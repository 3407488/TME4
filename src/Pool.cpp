#include "Pool.h"
#include "Job.h"

#include <iostream>
#include <thread>

namespace pr {

	Pool::Pool(int queueSize) : m_queue(queueSize), m_vector(){}


	Pool::~Pool(){}

	void Pool::start(int nbThread) {
		m_vector.reserve(nbThread);
		for (int i = 0; i < nbThread; i++) {
			// TODO je vois pas qu'elle fonction il faut pass� au thread.
			m_vector.emplace_back(std::thread(threadBody, &m_queue));
		}
	}

	void Pool::submit(Job *job) {
		m_queue.push(job);
	}
	
	void Pool::takeAndExecuteJob() {
		while (true) {
			Job* job = m_queue.pop();

			if (job != nullptr) {
				job->run();
			}
			else
				break;
		}

		std::cout << "Fin du thread = " << std::this_thread::get_id() << std::endl;
	}

	void Pool::stop() {
		// On debloque tout le monde.
		m_queue.setBlockingPop(false);

		for (auto it = m_vector.begin(); it != m_vector.end(); it++) {
			// On join les threads en cours.
			std::thread *t = &(*it);
			t->join();
		}
	}

	void threadBody(Queue<Job> *queue) {
		Job *j = nullptr;
		while ((j = queue->pop()) == nullptr) {
			j->run();
			delete j;
		}
	}
}