#include "AvtpStream.h"

namespace AvbTools
{
	AvtpStream::AvtpStream(const AvtpStreamInfo & streamInfo):
		mStreamInfo(streamInfo),
		mStreamData(std::set<AvtpStreamData, AvtpStreamData::AvtpStreamDataCompare>())
	{
	}

	void AvtpStream::AddAudioData(const AvtpStreamData & data)
	{
		mStreamData.insert(data);
	}

	AvtpStream::~AvtpStream()
	{
	}
}