#pragma once

#include "Job.h"

#include "Barrier.h"

namespace pr {

	class JobConcret :
		public Job
	{

	private:
		int m_arg;
		int* m_res;
		Barrier* m_barrier;

	public:
		JobConcret(int arg, int* res, Barrier* barrier);
		virtual ~JobConcret();

		virtual void run();
	};

}