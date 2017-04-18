#pragma once

#include <string>

#include "AvtpStreamInfo.h"

namespace AvbTools
{
	class AvtpStream
	{
	public:
		AvtpStream(const AvtpStreamInfo& streamInfo, const std::string& audioData);
		void AddAudioData(const std::string & data);
	private:
		std::string mAudioData;
		AvtpStreamInfo mStreamInfo;
	};
}
