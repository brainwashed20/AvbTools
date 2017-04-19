#include <sstream>

#include "AvtpStreamInfo.h"

namespace AvbTools
{
	const std::map<AvtpStreamInfo::IEEE1722_AAF_FORMAT, std::string> AvtpStreamInfo::kSoxAafFormatArgumentMap = {
		{ IEEE1722_AAF_FORMAT::USER, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::FLOAT_32_BIT, "floating-point" },
		{ IEEE1722_AAF_FORMAT::INT_32_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::INT_24_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::INT_16_BIT, "signed-integer" },
		{ IEEE1722_AAF_FORMAT::AES3_32_BIT, "signed-integer" }, // not very sure about this one
	};

	const std::map<AvtpStreamInfo::IEEE1722_AAF_NOMINAL_SAMPLE_RATE, std::string> AvtpStreamInfo::kSoxAafSampleRateArgumentMap = {
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_8kHz, "8000" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_16kHz, "16000" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_32kHz, "32000" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_44_1kHz, "44100" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_48kHz, "48000" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_88_2kHz, "88200" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_96kHz, "96000" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_176_4kHz, "176400" },
		{ IEEE1722_AAF_NOMINAL_SAMPLE_RATE::RATE_192kHz, "192000" },
	};

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

	AvtpStreamInfo::~AvtpStreamInfo()
	{
	}

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

	unsigned int AvtpStreamInfo::GetSampleRate() const
	{
		return mSampleRate;
	}
}