#pragma once

#include <atomic>
#include <string>

namespace AvbTools
{
	class AvtpToWav
	{
	public:

		enum class OperationStatus
		{
			ERROR_SERVICE_NOT_INITIALIZED,
			SUCCESS
		};

		struct Response
		{
			OperationStatus status;
			std::string message;

			Response(const OperationStatus _status, const std::string& _message) :
				status(_status),
				message(_message)
			{

			}
		};

		static AvtpToWav* getInstance();
		void init(const std::string& tsharkBin, const std::string& soxBin);

		Response convertToWav(const std::string& captureFile, const std::string& audioFile);

	private:

		AvtpToWav();

		static AvtpToWav* sInstance;
		static std::atomic<bool> sAquiredSingleton;

		bool mIsServiceInitialized;
		std::string mTsharkBin;
		std::string mSoxBin;
	};
}
