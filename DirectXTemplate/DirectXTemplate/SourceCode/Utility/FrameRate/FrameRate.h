#ifndef FRAME_RATE_H
#define FRAME_RATE_H

#include <Windows.h>

class CFrameRate
{
	const double FRAME_TIME;
public:
	CFrameRate( double fps = 60.0 );
	~CFrameRate();

	void Wait();

	static double GetFPS(){ return 1.0/m_FrameTime; }

private:
	
	static double	m_FrameTime;
	LARGE_INTEGER	m_StartTime;
	LARGE_INTEGER	m_NowTime;
	LARGE_INTEGER	m_FreqTime;
};

#endif	// #ifndef FRAME_RATE_H.