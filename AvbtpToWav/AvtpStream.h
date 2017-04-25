#pragma once

#include <string>
#include <set>
#include <vector>

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
		std::vector<std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>> mStreamData;
		std::vector<char> HexToBytes(const std::string& hex);
		AvtpStreamInfo mStreamInfo;
	};
}
