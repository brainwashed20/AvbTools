#include "AvtpStream.h"
namespace AvbTools
{
	AvtpStream::AvtpStream(const AvtpStreamInfo & streamInfo, const std::string & audioData):
		mStreamInfo(streamInfo),
		mAudioData(audioData)
	{
	}

	void AvtpStream::AddAudioData(const std::string & data)
	{
		mAudioData += "\n";
		mAudioData.append(data);
	}
}