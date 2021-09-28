#pragma once
#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"

/**
 * \brief A time measuring tool.
 *
 *     TicToc::tic();
 *
 *     sleep(5); // some time burning code
 *
 *     const auto elapsed_microseconds = TicToc::toc();
 *
 *     print(elapsed_microseconds); // use measurement
 *
 * It is possible to nest calls to tic() and toc().
 */
class TicToc
{
public:

	/**
	 * \brief Convenience shortcut for getting a current timestamp.
	 */
	static inline boost::posix_time::ptime now()
	{
		const auto now = boost::posix_time::microsec_clock::local_time();
		return now;
	}

	/**
	 * \brief Start timing.
	 */
	static inline void tic()
	{
		const auto now_ = now();
		getStack().push_back(now_);
	}

	/**
	 * \brief Stop timing.
	 * \return Elapsed time in microseconds.
	 */
	static inline long long toc()
	{
		if (getStack().empty())
			throw std::runtime_error("No start time defined. Make sure to call TicToc::tic() before.");

		const boost::posix_time::ptime start = getStack().back(); // access
		getStack().pop_back(); // remove

		const auto end = now();
		return (end - start).total_microseconds();
	}

	/**
	 * \brief Convenience shortcut for printing time measurement to std::cout.
	 * \param msg name or identifier of the measured functionality.
	 */
	static inline void tocAndCout(const std::string& msg)
	{
		const auto duration = toc();
		std::cout << "[TicToc] took " << duration << "us for " << msg << std::endl;
	}

private:
	TicToc() { }

	static std::vector<boost::posix_time::ptime>& getStack()
	{
		static std::vector<boost::posix_time::ptime> stack;
		return stack;
	}
};

