#include <fstream>
#include <algorithm>

#include "AvtpStream.h"

namespace AvbTools
{
	AvtpStream::AvtpStream(const AvtpStreamInfo & streamInfo):
		mStreamInfo(streamInfo),
		mStreamData(std::vector<std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>>())
	{
		mStreamData.push_back(std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>());
	}

	void AvtpStream::AddAudioData(const AvtpStreamData & data)
	{
		std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>& currentSet = mStreamData.back();

		if (currentSet.empty())
		{
			currentSet.insert(data);
		}
		else
		{
			
			if (std::prev(currentSet.end())->mSequenceNumber > data.mSequenceNumber)
			{
				// create a new one
				mStreamData.push_back(std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>());
				mStreamData.back().insert(data);
			}
			else
			{
				// append to the existing one
				currentSet.insert(data);
			}
		}
	}

	std::vector<char> AvtpStream::HexToBytes(const std::string& hex)
	{
		std::vector<char> bytes;

		for (unsigned int i = 0; i < hex.length(); i += 2)
		{
			std::string byteString = hex.substr(i, 2);
			char byte = (char)strtol(byteString.c_str(), NULL, 16);
			bytes.push_back(byte);
		}

		return bytes;
	}

	bool AvtpStream::WriteAsWav(const std::string & soxBin, const std::string & outputDir)
	{
		std::string audioFileName = mStreamInfo.GetSource() + "_" + mStreamInfo.GetDestination();
		std::replace(audioFileName.begin(), audioFileName.end(), ':', '_');
		
		std::string rawDataFile = audioFileName + ".raw";
		std::replace(rawDataFile.begin(), rawDataFile.end(), ':', '_');
	
		// create hex array
		std::string hexData;
		for (auto& container : mStreamData)
		{
			for (auto& data : container)
			{
				std::string str(data.mAudioData);
				str.erase(std::remove(str.begin(), str.end(), ':'), str.end());
				hexData += str;
			}
		}

		// write binary array to disk
		std::vector<char> binaryData = HexToBytes(hexData);
		std::ofstream g(outputDir + "\\" + rawDataFile, std::ofstream::out | std::ofstream::binary);
		g.write(binaryData.data(), binaryData.size());
		g.close();

		// now call sox
		std::string wavAudioFile = audioFileName + ".wav";
		char buf[400];
		sprintf_s(buf,
			"%s -r %u -e %s -b %u -c %u %s %s",
			soxBin.c_str(),
			AvtpStreamInfo::kSoxAafSampleRateArgumentMap[mStreamInfo.GetSampleRate()],
			AvtpStreamInfo::kSoxAafFormatArgumentMap[mStreamInfo.GetAafFormat()].c_str(),
			mStreamInfo.GetBitDepth(),
			mStreamInfo.GetChannelsPerFrame(),
			(outputDir + "\\" + rawDataFile).c_str(),
			(outputDir + "\\" + wavAudioFile).c_str());

		const std::string soxCmd(buf);

		int ret = std::system(soxCmd.c_str());

		return (ret == 0);
	}

	bool AvtpStream::IsStreamValid() const
	{
		return mStreamInfo.GetBitDepth() > 0
			&& mStreamInfo.GetChannelsPerFrame() > 0
			&& mStreamInfo.GetSampleRate() != AvtpStreamInfo::IEEE1722_AAF_NOMINAL_SAMPLE_RATE::NONE
			&& mStreamInfo.GetAafFormat() != AvtpStreamInfo::IEEE1722_AAF_FORMAT::NONE
			&& !mStreamInfo.GetSource().empty()
			&& !mStreamInfo.GetDestination().empty()
			&& !mStreamData.empty();
	}

	AvtpStream::~AvtpStream()
	{
	}

	
}