#pragma once

#include <cstdio>

#include "AvtpToWav.h"

namespace AvbTools
{
	std::atomic<bool> AvtpToWav::sAquiredSingleton(false);

	AvtpToWav * AvtpToWav::getInstance()
	{
		if (sAquiredSingleton.load(std::memory_order_relaxed) == false)
		{
			sInstance = new AvtpToWav();
			sAquiredSingleton = true;
		}

		return sInstance;
	}

	void AvtpToWav::init(const std::string & tsharkBin, const std::string & soxBin)
	{
		sInstance->mTsharkBin = tsharkBin;
		sInstance->mSoxBin = soxBin;
		mIsServiceInitialized = true;
	}

	AvtpToWav::Response AvtpToWav::convertToWav(const std::string & captureFile, const std::string & audioFile)
	{
		if (!mIsServiceInitialized)
		{
			return Response(AvtpToWav::OperationStatus::ERROR_SERVICE_NOT_INITIALIZED, "Call init first");
		}

		// output to a file the necessary fields 
		// tshark.exe -r ____AA_03_avb_ALEV4.pcapng -T json > cacca.txt -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e eth.dst -e eth.src
		char tsharkCommand[400];
		// sprintf(tsharkCommand, "%s -r %s -T json > %s -e aaf.data -e aaf.nominal_sample_rate -e aaf.channels_per_frame -e aaf.bit_depth -e eth.dst -e eth.src", mTsharkBin.c_str(), captureFile, );
	
	}

	AvtpToWav::AvtpToWav() :
		mIsServiceInitialized(false),
		mTsharkBin(std::string()),
		mSoxBin(std::string())
	{
	}
}