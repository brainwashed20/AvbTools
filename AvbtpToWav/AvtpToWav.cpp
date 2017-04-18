#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../thirdparty/rapidjson/document.h"

#include "AvtpStream.h"
#include "AvtpToWav.h"

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

	AvtpToWav::Response AvtpToWav::convertToWav(const std::string & captureFile, const std::string & audioFile)
	{
		if (!mIsServiceInitialized)
		{
			return Response(AvtpToWav::OperationStatus::ERROR_SERVICE_NOT_INITIALIZED, "Call AvbTools::AvtpToWav::getInstance()->init(..) first");
		}

		// output to a file the necessary fields 
		// tshark.exe -r ____AA_03_avb_ALEV4.pcapng -T json > cacca.txt -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e eth.dst -e eth.src

		//std::string packetsFile = GetRandomStr(10) + ".raw";
		std::string packetsFile = mTempDir + "//" + "ceva2.raw";

		/*char buf[400];
		sprintf_s(buf,
			"%s -r %s -T json > %s -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e eth.dst -e eth.src",
			mTsharkBin.c_str(), captureFile.c_str(), packetsFile.c_str());

		const std::string dumpPacketsCommand(buf);
		int res = std::system(dumpPacketsCommand.c_str());
		if (res != 0)
		{
			return Response(AvtpToWav::OperationStatus::ERROR_FAILED_TO_DUMP_PACKETS, "Check if the paths for Tshark and capture file and valid");
		}
		*/

		std::string jsonPacketsFile = ReadPacketsFile(packetsFile);

		rapidjson::Document jsonDoc;
		jsonDoc.Parse(jsonPacketsFile.c_str());

		if (jsonDoc.HasParseError()
			|| !jsonDoc.IsArray())
		{
			return Response(AvtpToWav::OperationStatus::ERROR_FAILED_TO_PARSE_PACKETS_FILE, "possible corrupt .pcap file");
		}

		std::unordered_map<std::string, AvbTools::AvtpStream> streams;

		for (auto& v : jsonDoc.GetArray())
		{
			std::string streamSource = v["_source"]["layers"]["eth.src"].GetArray()[0].GetString();
			std::string streamDestionation = v["_source"]["layers"]["eth.dst"].GetArray()[0].GetString();
			unsigned int bitDepth = static_cast<unsigned int>(std::atoi(v["_source"]["layers"]["aaf.bit_depth"].GetArray()[0].GetString()));
			unsigned int channelsPerFrame = static_cast<unsigned int>(std::atoi(v["_source"]["layers"]["aaf.channels_per_frame"].GetArray()[0].GetString()));
			unsigned int nominalSampleRate = HexToUint(v["_source"]["layers"]["aaf.nominal_sample_rate"].GetArray()[0].GetString());
			std::string audioRawData = v["_source"]["layers"]["aaf.data"].GetArray()[0].GetString();
			
		}

		
	}

	std::string AvtpToWav::ReadPacketsFile(const std::string & path)
	{
		std::ifstream onStream(path.c_str(), std::ios::in);

		std::ostringstream ss;
		ss << onStream.rdbuf();

		return ss.str();
	}

	AvtpToWav::AvtpToWav() :
		mIsServiceInitialized(false),
		mTsharkBin(std::string()),
		mSoxBin(std::string()),
		mTempDir(std::string())
	{
	}

	std::string AvtpToWav::GetRandomStr(const int len)
	{
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		std::string res;

		for (int i = 0; i < len; ++i)
		{
			res.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
		}

		return res;
	}

	unsigned int AvtpToWav::HexToUint(const std::string & hexVal)
	{
		std::stringstream converter(hexVal);
		unsigned int value;
		converter >> std::hex >> value;
		return value;
	}
}