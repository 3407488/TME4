#pragma once

#include "Queue.h"
#include "Job.h"

#include <vector>
#include <thread>

namespace pr {

	class Pool
	{

	private:
		Queue<Job> m_queue;
		std::vector<std::thread> m_vector;

	public:
		Pool(int queueSize);
		virtual ~Pool();

		void start(int nbThread);

		void submit(Job *job);

		void stop();

		void takeAndExecuteJob();
	};
}