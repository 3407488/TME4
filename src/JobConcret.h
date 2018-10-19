#pragma once
#include "Job.h"

namespace pr {

	class JobConcret :
		public Job
	{

	private:
		int m_arg;
		int* m_res;

	public:
		JobConcret(int arg, int* res);
		virtual ~JobConcret();

		virtual void run();
	};

}