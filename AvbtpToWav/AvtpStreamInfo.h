#pragma once

#include <string>

namespace AvbTools
{
	class AvtpStreamInfo
	{
	public:
		AvtpStreamInfo(const std::string & source, const std::string & dest, const unsigned int bitDepth, const unsigned int channelsPerFrame, const unsigned int sampleRate);
		std::string ToString();
	private:
		std::string mSource;
		std::string mDestination;
		unsigned int mBitDepth;
		unsigned int mChannelsPerFrame;
		unsigned int mSampleRate;
	};
}