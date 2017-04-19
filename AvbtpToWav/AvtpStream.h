#pragma once

#include <string>
#include <set>

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

		std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare> mStreamData;
		AvtpStreamInfo mStreamInfo;
	};
}
