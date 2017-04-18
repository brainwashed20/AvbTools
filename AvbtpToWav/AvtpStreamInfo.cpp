#include <sstream>

#include "AvtpStreamInfo.h"

namespace AvbTools
{
	AvtpStreamInfo::AvtpStreamInfo(const std::string & source, const std::string & dest, const unsigned int bitDepth, const unsigned int channelsPerFrame, const unsigned int sampleRate):
		mBitDepth(bitDepth),
	    mSource(source),
		mDestination(dest),
	    mChannelsPerFrame(channelsPerFrame),
	    mSampleRate(sampleRate)
	{
	}

	std::string AvtpStreamInfo::ToString()
	{
		std::ostringstream ss;
		ss << mSource << "#" << mDestination << "#" << mChannelsPerFrame << "#" << mSampleRate << "#" << mBitDepth;
		return ss.str();
	}
}