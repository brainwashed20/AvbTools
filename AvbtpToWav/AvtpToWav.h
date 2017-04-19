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
			ERROR_FAILED_TO_DUMP_PACKETS,
			ERROR_FAILED_TO_PARSE_PACKETS_FILE,
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
		void init(const std::string & tempDir, const std::string& tsharkBin, const std::string& soxBin);

		Response convertToWav(const std::string& captureFile, const std::string& outputFolder);

	private:

		AvtpToWav();

		static AvtpToWav* sInstance;
		static std::atomic<bool> sAquiredSingleton;

		bool mIsServiceInitialized;
		std::string mTsharkBin;
		std::string mSoxBin;
		std::string mTempDir;

		std::string AvtpToWav::GetRandomStr(const int len);

		unsigned int HexToUint(const std::string & hexVal);
	};
}
