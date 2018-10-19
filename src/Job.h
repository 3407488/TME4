#pragma once

namespace pr {

	class Job
	{
	public:
		Job();
		virtual ~Job();

		virtual void run() = 0;
	};

}