#pragma once

#include <mutex>

namespace pr {

	class Barrier {

	private:
		mutable std::recursive_mutex m_mutex;

		std::condition_variable m_condition;

		int m_nbAttente;

		int m_nbFinish;

	public:
		Barrier(int nbAttente);
		virtual ~Barrier();

		void done();

		void waitFor();

	};

}