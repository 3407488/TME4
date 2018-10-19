#include "Barrier.h"

#include <iostream>
#include <mutex>

namespace pr {

	Barrier::Barrier(int nbAttente) : m_nbAttente(nbAttente), m_nbFinish(0) {}

	Barrier::~Barrier() {}

	void Barrier::done() {
		std::unique_lock<std::recursive_mutex> lock(m_mutex);

		m_nbFinish++;

		lock.unlock();

		m_condition.notify_all();
	}

	void Barrier::waitFor() {
		std::unique_lock<std::recursive_mutex> lock(m_mutex);
	
		while (m_nbFinish < m_nbAttente) {
			m_condition.wait(lock);
		}

		std::cout << "Fin du wait for" << endl;
	}

}