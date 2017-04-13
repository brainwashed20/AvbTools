#include <vector>
#include <thread>
#include <atomic>

#include "Job.h"

namespace TShark 
{
	class TSharkManager
	{
	public:
		static const unsigned int k_MaxNumThreads;
		static const unsigned int k_JobsCheckInterval;

		static TSharkManager* GetInstance();
		
		void QueueJob(const std::string& command, TSharkResponse callback);

		~TSharkManager();
	private:
		static TSharkManager* m_Instance;
		static std::atomic<bool> s_AquiredSingletonInstance;

		TSharkManager();
		std::vector<std::pair<Job*, std::thread>> m_RunningJobs;
		std::vector<Job*> m_PendingJobs;
		std::thread m_DaemonCheckerThread;
		void CheckJobs();
	};
}