#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <unordered_map>

#include "../thirdparty/rapidjson/document.h"
#include "../thirdparty/rapidjson/filereadstream.h"

#include "AvtpToWav.h"
#include "AvtpStream.h"


namespace AvbTools
{
	std::atomic<bool> AvtpToWav::sAquiredSingleton(false);
	AvtpToWav* AvtpToWav::sInstance(nullptr);

	AvtpToWav * AvtpToWav::getInstance()
	{
		if (sAquiredSingleton.load(std::memory_order_relaxed) == false)
		{
			sInstance = new AvtpToWav();
			sAquiredSingleton = true;
		}

		return sInstance;
	}

	void AvtpToWav::init(const std::string & tempDir, const std::string& tsharkBin, const std::string& soxBin)
	{
		mTempDir = tempDir;
		mTsharkBin = tsharkBin;
		mSoxBin = soxBin;
		mIsServiceInitialized = true;
	}

	AvtpToWav::Response AvtpToWav::convertToWav(const std::string & captureFile, const std::string & outputFolder)
	{
		if (!mIsServiceInitialized)
		{
			return Response(AvtpToWav::OperationStatus::ERROR_SERVICE_NOT_INITIALIZED, "Call AvbTools::AvtpToWav::getInstance()->init(..) first");
		}

		// output to a file the necessary fields 
		// tshark.exe -r ____AA_03_avb_ALEV4.pcapng -T json > cacca.txt -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e eth.dst -e eth.src

		std::string packetsFile = mTempDir + "//" + GetFilenameFromPath(captureFile) + ".json";

		char buf[400];
		sprintf_s(buf,
			"%s -r %s -T json > %s -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e aaf.seqnum -e aaf.avtp_timestamp -e aaf.format_info -e eth.dst -e eth.src",
			mTsharkBin.c_str(), captureFile.c_str(), packetsFile.c_str());

		const std::string dumpPacketsCommand(buf);
		int res = std::system(dumpPacketsCommand.c_str());
		if (res != 0)
		{
			return Response(AvtpToWav::OperationStatus::ERROR_FAILED_TO_DUMP_PACKETS, "Check if the paths for Tshark and capture file and valid");
		}

		FILE* fp = fopen(packetsFile.c_str(), "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(is);
		fclose(fp);

		if (jsonDoc.HasParseError()
			|| !jsonDoc.IsArray())
		{
			return Response(AvtpToWav::OperationStatus::ERROR_FAILED_TO_PARSE_PACKETS_FILE, "possible corrupt .pcap file");
		}

		std::unordered_map<std::string, std::unique_ptr<AvtpStream>> streams;

		for (auto& v : jsonDoc.GetArray())
		{
			const rapidjson::Value& elem = v["_source"]["layers"];

			const std::string streamSource = elem.HasMember("eth.src") ?
				elem["eth.src"].GetArray()[0].GetString() : "";

			const std::string streamDestination = elem.HasMember("eth.dst") ?
				elem["eth.dst"].GetArray()[0].GetString() : "";

			const unsigned int bitDepth = elem.HasMember("aaf.bit_depth") ?
				static_cast<unsigned int>(std::atoi(elem["aaf.bit_depth"].GetArray()[0].GetString())) : 0;

			const unsigned int channelsPerFrame = elem.HasMember("aaf.channels_per_frame") ?
				static_cast<unsigned int>(std::atoi(elem["aaf.channels_per_frame"].GetArray()[0].GetString())) : 0;

			const unsigned int nominalSampleRate = elem.HasMember("aaf.nominal_sample_rate") ?
				HexToUint(elem["aaf.nominal_sample_rate"].GetArray()[0].GetString()) : 0;

			const std::string audioRawData = elem.HasMember("aaf.data") ?
				elem["aaf.data"].GetArray()[0].GetString() : "";

			const std::string avtpTimestamp = elem.HasMember("aaf.avtp_timestamp") ?
				elem["aaf.avtp_timestamp"].GetArray()[0].GetString() : "";

			const unsigned int sequenceNumber = elem.HasMember("aaf.seqnum") ?
				static_cast<unsigned int>(std::atoi(elem["aaf.seqnum"].GetArray()[0].GetString())) : 0;

			const unsigned int aafFormat = elem.HasMember("aaf.format_info") ?
				HexToUint(elem["aaf.format_info"].GetArray()[0].GetString()) : 0;

			AvtpStreamInfo streamInfo = AvbTools::AvtpStreamInfo(streamSource, streamDestination, bitDepth, channelsPerFrame, nominalSampleRate, aafFormat);

			const std::string hashKey(streamInfo.ToString());
			if (streams.find(hashKey) == streams.end())
			{
				streams[hashKey] = std::unique_ptr<AvtpStream>(new AvtpStream(streamInfo));
			}
			streams[hashKey]->AddAudioData(AvtpStreamData(audioRawData, sequenceNumber, avtpTimestamp));
		}

		for (const auto& v : streams)
		{
			AvtpStream* stream = v.second.get();
			if (stream->IsStreamValid())
			{
				stream->WriteAsWav(mSoxBin, outputFolder);
			}
		}

		return Response(AvtpToWav::OperationStatus::SUCCESS, "check output folder");
	}

	AvtpToWav::AvtpToWav() :
		mIsServiceInitialized(false),
		mTsharkBin(std::string()),
		mSoxBin(std::string()),
		mTempDir(std::string())
	{
	}

	unsigned int AvtpToWav::HexToUint(const std::string & hexVal)
	{
		std::stringstream converter(hexVal);
		unsigned int value;
		converter >> std::hex >> value;
		return value;
	}

	std::string AvtpToWav::GetFilenameFromPath(const std::string & path)
	{
		char buf[100], buf2[100], buf3[100], buf4[100];
		_splitpath_s(path.c_str(), buf, buf2, buf3, buf4);
		return std::string(buf3);
	}
}