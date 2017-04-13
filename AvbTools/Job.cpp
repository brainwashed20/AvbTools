#include "Job.h"

namespace TShark
{
	// 1 min in ms
	const unsigned int Job::k_DefaultTimeoutJob(60000);

	Job::Job(const std::string& command, TSharkResponse callback, unsigned int timeout) :
		m_TSharkCommand(command),
		m_Callback(callback),
		m_Status(JobStatus::PENDING_TO_START),
		m_StartTime(std::chrono::system_clock::time_point::max()),
		m_Timeout(timeout)
	{
	}

	void Job::Run()
	{
		m_StartTime = std::chrono::system_clock::now();
		m_Status = JobStatus::RUNNING;

		std::string result = "result";
		JobError error = JobError::NO_ERROR;

		m_Status = JobStatus::FINISHED;
		m_Callback(result, error);
	}

	std::chrono::system_clock::time_point Job::GetStartTime()
	{
		return m_StartTime;
	}

	unsigned int Job::GetTimeoutValue() const
	{
		return m_Timeout;
	}

	JobStatus Job::GetStatus() const
	{
		return JobStatus();
	}

	std::string Job::GetTSharkCommand() const
	{
		return m_TSharkCommand;
	}
}
