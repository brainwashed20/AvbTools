#pragma once

#include <string>

namespace AvbTools
{
	class AvtpStreamData
	{
	public:
		AvtpStreamData(const std::string & audioData, const unsigned int sequenceNumber, const std::string & avtpTimestamp);
		
		std::string mAudioData;
		unsigned int mSequenceNumber;
		std::string mAvtpTimestamp;
	};
}