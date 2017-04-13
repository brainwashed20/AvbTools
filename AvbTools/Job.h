#include <string>
#include <functional>
#include <chrono>

namespace TShark
{
	enum class JobError
	{
		NO_ERROR,
	};

	enum class JobStatus
	{
		PENDING_TO_START,
		RUNNING,
		FINISHED
	};

	typedef std::function<void(const std::string, JobError)> TSharkResponse;

	class Job
	{
	public:
		static const unsigned int k_DefaultTimeoutJob;
		Job(const std::string& command, TSharkResponse callback, unsigned int timeout = Job::k_DefaultTimeoutJob);
		void Run();
		std::chrono::system_clock::time_point GetStartTime();
		JobStatus GetStatus() const;
		std::string GetTSharkCommand() const;
		unsigned int GetTimeoutValue() const;

	private:
		std::string m_TSharkCommand;
		TSharkResponse m_Callback;
		JobStatus m_Status;
		std::chrono::system_clock::time_point m_StartTime;
		unsigned int m_Timeout;
	};
}