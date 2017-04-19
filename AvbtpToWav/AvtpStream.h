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
		~AvtpStream();
		
		void AddAudioData(const AvtpStreamData & streamData);
		bool WriteAsWav(const std::string & soxBin, const std::string & outputDir);
		bool IsStreamValid() const;

	private:

		std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare> mStreamData;
		AvtpStreamInfo mStreamInfo;
	};
}
