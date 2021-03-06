#pragma once

#include <string>
#include <map>

namespace AvbTools
{
	class AvtpStreamInfo
	{
	public:
		
		// data taken from https://github.com/wireshark/wireshark/blob/9f71c86880cb5c3eab65c82e6fb3d32e603f3709/epan/dissectors/packet-ieee1722.c
		enum class IEEE1722_AAF_FORMAT
		{
			NONE = -1,
			USER = 0,
			FLOAT_32_BIT = 1,
			INT_32_BIT = 2,
			INT_24_BIT = 3,
			INT_16_BIT = 4,
			AES3_32_BIT = 5
		};

		static std::map<IEEE1722_AAF_FORMAT, std::string> kSoxAafFormatArgumentMap;

		enum class IEEE1722_AAF_NOMINAL_SAMPLE_RATE
		{
			NONE = -1,
			RATE_8kHz = 1,
			RATE_16kHz = 2,
			RATE_32kHz = 3,
			RATE_44_1kHz = 4,
			RATE_48kHz = 5,
			RATE_88_2kHz = 6,
			RATE_96kHz = 7,
			RATE_176_4kHz = 8,
			RATE_192kHz = 9,
            RATE_24kHz = 10
		};

		static std::map<IEEE1722_AAF_NOMINAL_SAMPLE_RATE, unsigned int> kSoxAafSampleRateArgumentMap;

		AvtpStreamInfo(const std::string & source, const std::string & dest, const unsigned int bitDepth, const unsigned int channelsPerFrame, const unsigned int sampleRate, const unsigned int format);
		std::string ToString();
		~AvtpStreamInfo();

		std::string GetSource() const;
		std::string GetDestination() const;
		unsigned int GetBitDepth() const;
		unsigned int GetChannelsPerFrame() const;
		IEEE1722_AAF_NOMINAL_SAMPLE_RATE GetSampleRate() const;
		IEEE1722_AAF_FORMAT GetAafFormat() const;

	private:
		std::string mSource;
		std::string mDestination;
		unsigned int mBitDepth;
		unsigned int mChannelsPerFrame;
		IEEE1722_AAF_NOMINAL_SAMPLE_RATE mSampleRate;
		IEEE1722_AAF_FORMAT mFormat;
	};
}