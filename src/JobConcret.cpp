#include "JobConcret.h"

#include "Barrier.h"

#include <iostream>
#include <thread>

namespace pr {

	JobConcret::JobConcret(int arg, int* res, Barrier* barrier) : m_arg(arg), m_res(res), m_barrier(barrier){}


	JobConcret::~JobConcret(){}

	void JobConcret::run() {
		std::cout << "Début sur agrs = " << m_arg << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		*m_res = m_arg % 256;

		std::cout << "Fini sur args = " << m_arg << " res = " << (*m_res) << std::endl;

		m_barrier->done();
	}
}
