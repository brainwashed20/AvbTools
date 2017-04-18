#include "AvtpStream.h"

namespace AvbTools
{
	AvtpStream::AvtpStream(const AvtpStreamInfo & streamInfo):
		mStreamInfo(streamInfo),
		mStreamData(std::vector<AvtpStreamData>())
	{
	}

	void AvtpStream::AddAudioData(const AvtpStreamData & data)
	{
		mStreamData.push_back(data);
	}

	AvtpStream::~AvtpStream()
	{
	}
}