#include "AvtpStreamData.h"

namespace AvbTools
{
	AvtpStreamData::AvtpStreamData(const std::string & audioData, const unsigned int sequenceNumber, const std::string & avtpTimestamp):
		mAudioData(audioData),
		mSequenceNumber(sequenceNumber),
		mAvtpTimestamp(avtpTimestamp)
	{
	}
}