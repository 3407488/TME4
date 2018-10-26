#pragma once

#include <string> //size_t
#include <mutex>

namespace pr {

	template<typename T>
	class Queue
	{

	private:
		mutable std::mutex m_mutex;

		std::condition_variable m_conditionPop;
		std::condition_variable m_conditionPush;

		T ** m_tab;
		const size_t m_maxsize;
		size_t m_begin;
		size_t m_size;
		bool m_isBlocking;

		bool full() const {
			std::unique_lock<std::mutex> lock(m_mutex);
			return m_size == m_maxsize;
		}

		bool empty() const {
			std::unique_lock<std::recursive_mutex> lock(m_mutex);
			return m_size == 0;
		}

	public:
		Queue(size_t maxsize) : m_maxsize(maxsize), m_begin(0), m_size(0), m_isBlocking(true) {
			m_tab = new T*[maxsize];
			memset(m_tab, 0, maxsize * sizeof(T*));
		}

		virtual ~Queue() {
			std::unique_lock<std::mutex> lock(m_mutex);
			for (size_t i = 0; i < m_size; i++) {
				auto ind = (m_begin + i) % m_maxsize;
				delete m_tab[ind];
			}
			delete[] m_tab;
		}

		size_t size() const {
			return m_size;
		}

		T* pop() {
			std::unique_lock<std::mutex> lock(m_mutex);

			if (m_isBlocking) {
				//m_conditionPop.wait(lock, [this]{return empty() && m_isBlocking;});
				while (empty() && m_isBlocking)
					m_conditionPop.wait(lock);
			}

			if (!empty()) {
				auto ret = m_tab[m_begin];
				m_tab[m_begin] = nullptr;
				m_size--;
				m_begin = (m_begin + 1) % m_maxsize;

				lock.unlock();
				m_conditionPush.notify_all();

				return ret;
			}
			else
				return nullptr;
		}

		bool push(T* elt) {
			if (elt == nullptr)
			return false;

			std::unique_lock<std::mutex> lock(m_mutex);
			
			// m_conditionPush.wait(lock, [this]{return full();});

			while (full()) {
				m_conditionPush.wait(lock);
			}

			if (!full() && elt != nullptr) {
				m_tab[(m_begin + m_size) % m_maxsize] = elt;
				m_size++;

				lock.unlock();
				m_conditionPop.notify_all();

				return true;
			}
			else
				return false;
		}

		void setBlockingPop(bool isBlocking) {
			std::unique_lock<std::mutex> lock(m_mutex);
			m_isBlocking = isBlocking;

			if (m_isBlocking) {
				lock.unlock();

				m_conditionPop.notify_all();
			}
		}
	};
}

