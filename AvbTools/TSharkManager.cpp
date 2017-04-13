#include <iostream>

#include "TSharkManager.h"

namespace TShark
{
	const unsigned int TSharkManager::k_MaxNumThreads(10);
	
	// 5 seconds in ms
	const unsigned int TSharkManager::k_JobsCheckInterval(5000);

	std::atomic<bool> TSharkManager::s_AquiredSingletonInstance(false);
	TSharkManager* TSharkManager::m_Instance(nullptr);
	
	TSharkManager::TSharkManager():
		m_RunningJobs(std::vector<std::pair<Job*, std::thread>>()),
		m_PendingJobs(std::vector<Job*>())
	{
		m_DaemonCheckerThread = std::thread(&TSharkManager::CheckJobs, this);
	}

	void TSharkManager::CheckJobs()
	{
		while (1)
		{
			// todo

			std::this_thread::sleep_for(std::chrono::milliseconds(TSharkManager::k_JobsCheckInterval));
		}
	}

	TSharkManager* TSharkManager::GetInstance()
	{
		if (TSharkManager::s_AquiredSingletonInstance.load(std::memory_order_relaxed) == false) 
		{
			m_Instance = new TSharkManager();
			s_AquiredSingletonInstance = true;
		}

		return m_Instance;
	}

	void TSharkManager::QueueJob(const std::string & command, TSharkResponse callback)
	{
		m_PendingJobs.push_back(new Job(command, callback));
	}

	TSharkManager::~TSharkManager()
	{
		if (m_DaemonCheckerThread.joinable())
		{
			m_DaemonCheckerThread.join();
		}
		else
		{
			m_DaemonCheckerThread.detach();
		}
	}
}