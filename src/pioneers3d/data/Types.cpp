#include <pioneers3d/data/Types.hpp>

#include <windows.h>
#include <time.h>

namespace pioneers3d
{

int64_t
getPerfTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter( &li );
	return static_cast< int64_t >( li.QuadPart );
}

int64_t
getPerfTimerFrequency()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency( &li );
	return static_cast< int64_t >( li.QuadPart );
}

std::string printDate()
{
	tm * t = localtime( nullptr );
	std::stringstream s;
	s   << t->tm_year << "-" << t->tm_mon << "-" << t->tm_mday << " "
		<< t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec;
	return s.str();
}

std::string printSystemTime()
{
	SYSTEMTIME t;
	GetSystemTime( &t );
	std::stringstream s;
	s   << t.wYear << "-" << t.wMonth << "-" << t.wDay << " "
		<< t.wHour << ":" << t.wMinute << ":" << t.wSecond << "." << t.wMilliseconds;
	return s.str();
}

std::string printLocalTime()
{
	SYSTEMTIME t;
	GetLocalTime( &t );
	std::stringstream s;
	s   << t.wYear << "-" << t.wMonth << "-" << t.wDay << " "
		<< t.wHour << ":" << t.wMinute << ":" << t.wSecond << "." << t.wMilliseconds;
	return s.str();
}

std::string printTimer()
{
	std::stringstream s;
	s   << getPerfTimer() << ", f=" << getPerfTimerFrequency() << " Hz\n";
	return s.str();
}

} // end namespace pioneers3d
