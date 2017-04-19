#include <sstream>

#include "AvtpStreamInfo.h"

namespace AvbTools
{
	std::map<AvtpStreamInfo::IEEE1722_AAF_FORMAT, std::string> AvtpStreamInfo::kSoxAafFormatArgumentMap = {
		{ IEEE1722_AAF_FORMAT::USER, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::FLOAT_32_BIT, "floating-point" },
		{ IEEE1722_AAF_FORMAT::INT_32_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::INT_24_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::INT_16_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::AES3_32_BIT, "signed-integer" }, // not very sure about this one
	};

	std::map<AvtpStreamInfo::IEEE1722_AAF_NOMINAL_SAMPLE_RATE, unsigned int> AvtpStreamInfo::kSoxAafSampleRateArgumentMap = {
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_8kHz, 8000 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_16kHz, 16000 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_32kHz, 32000 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_44_1kHz, 44100 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_48kHz, 48000 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_88_2kHz, 88200 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_96kHz, 96000 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_176_4kHz, 176400 },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_192kHz, 192000 },
	};

	AvtpStreamInfo::AvtpStreamInfo(const std::string & source, const std::string & dest, const unsigned int bitDepth, const unsigned int channelsPerFrame, const unsigned int sampleRate, const unsigned int format) :
		mBitDepth(bitDepth),
		mSource(source),
		mDestination(dest),
		mChannelsPerFrame(channelsPerFrame)
	{
		switch (sampleRate)
		{
		case 1: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_8kHz; break; }
		case 2: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_16kHz; break; }
		case 3: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_32kHz; break; }
		case 4: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_44_1kHz; break; }
		case 5: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_48kHz; break; }
		case 6: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_88_2kHz; break; }
		case 7: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_96kHz; break; }
		case 8: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_176_4kHz; break; }
		case 9: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_192kHz; break; }
		default: { mSampleRate = IEEE1722_AAF_NOMINAL_SAMPLE_RATE::NONE; break; }
		}

		switch (format)
		{
		case 0: { mFormat = IEEE1722_AAF_FORMAT::USER; break; }
		case 1: { mFormat = IEEE1722_AAF_FORMAT::FLOAT_32_BIT; break; }
		case 2: { mFormat = IEEE1722_AAF_FORMAT::INT_32_BIT; break; }
		case 3: { mFormat = IEEE1722_AAF_FORMAT::INT_24_BIT; break; }
		case 4: { mFormat = IEEE1722_AAF_FORMAT::INT_16_BIT; break; }
		case 5: { mFormat = IEEE1722_AAF_FORMAT::AES3_32_BIT; break; }
		default: { mFormat = IEEE1722_AAF_FORMAT::NONE; break; }
		}
	}

	std::string AvtpStreamInfo::ToString()
	{
		std::ostringstream ss;
		ss << mSource << "#" << mDestination << "#" << mChannelsPerFrame << "#" << (unsigned int)mSampleRate << "#" << mBitDepth << "#" << (unsigned int)mFormat;
		return ss.str();
	}

	AvtpStreamInfo::~AvtpStreamInfo()
	{}

	std::string AvtpStreamInfo::GetSource() const
	{
		return mSource;
	}

	std::string AvtpStreamInfo::GetDestination() const
	{
		return mDestination;
	}

	unsigned int AvtpStreamInfo::GetBitDepth() const
	{
		return mBitDepth;
	}

	unsigned int AvtpStreamInfo::GetChannelsPerFrame() const
	{
		return mChannelsPerFrame;
	}

	AvtpStreamInfo::IEEE1722_AAF_NOMINAL_SAMPLE_RATE AvtpStreamInfo::GetSampleRate() const 
	{
		return mSampleRate;
	}

	AvtpStreamInfo::IEEE1722_AAF_FORMAT AvtpStreamInfo::GetAafFormat() const
	{
		return mFormat;
	}
}