#include "Logger.hpp"
#include "Common.hpp"

#include <cstdio>
#include <stdexcept>

#include <boost/thread/mutex.hpp>

typedef boost::mutex Mut;
typedef boost::unique_lock<Mut> Lock;

static Mut ioProtection;

static void write(const char* type, const char* tag, const char* message)
{
	Lock w(ioProtection);
	printf("%s -> [%s]: %s\n", type, tag, message);
}

namespace Logger
{
#ifdef DEBUG
	void Handle::Debug(const char* message) const
	{
		write("D", tag, message);
	}
#endif

	void Handle::Fatal(const char* message) const
	{
		write("F", tag, message);
		throw std::runtime_error(message);
	}
}