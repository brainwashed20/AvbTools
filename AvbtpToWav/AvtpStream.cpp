#include <fstream>
#include <algorithm>

#include "AvtpStream.h"

namespace AvbTools
{
	AvtpStream::AvtpStream(const AvtpStreamInfo & streamInfo):
		mStreamInfo(streamInfo),
		mStreamData(std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>())
	{
	}

	void AvtpStream::AddAudioData(const AvtpStreamData & data)
	{
		mStreamData.insert(data);
	}

	bool AvtpStream::WriteAsWav(const std::string & soxBin, const std::string & outputDir)
	{
		std::string audioFileName = mStreamInfo.GetSource() + "_" + mStreamInfo.GetDestination();
		std::replace(audioFileName.begin(), audioFileName.end(), ':', '_');
		
		// write raw data to file first
		std::string rawDataFile = audioFileName + ".raw";
		std::replace(rawDataFile.begin(), rawDataFile.end(), ':', '_');
		std::ofstream g(outputDir + "\\" + rawDataFile);
		for (const auto& data : mStreamData)
		{
			g << data.mAudioData;
		}
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
			5,
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