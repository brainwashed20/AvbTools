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
		std::string rawAudioFile = mStreamInfo.ToString() + ".raw";
		std::replace(rawAudioFile.begin(), rawAudioFile.end(), ':', '_');
		std::ofstream g(outputDir + "\\" + rawAudioFile);

		for (const auto& data : mStreamData)
		{
			g << data.mAudioData;
		}

		g.close();



		return true;
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