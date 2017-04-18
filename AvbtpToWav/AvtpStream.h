#pragma once

#include <string>
#include <vector>

#include "AvtpStreamInfo.h"
#include "AvtpStreamData.h"

namespace AvbTools
{
	class AvtpStream
	{
	public:
		AvtpStream(const AvtpStreamInfo& streamInfo);
		void AddAudioData(const AvtpStreamData & streamData);
		~AvtpStream();

		std::vector<AvtpStreamData> mStreamData;
		AvtpStreamInfo mStreamInfo;
	};
}
