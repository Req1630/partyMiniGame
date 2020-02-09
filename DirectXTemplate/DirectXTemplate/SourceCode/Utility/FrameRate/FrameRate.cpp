#include "FrameRate.h"

double CFrameRate::m_FrameTime = 0.0;

CFrameRate::CFrameRate( double fps )
	: FRAME_TIME	( 1.0 / fps )
	, m_StartTime	()
	, m_NowTime		()
	, m_FreqTime	()
{
	QueryPerformanceFrequency( &m_FreqTime );
	QueryPerformanceCounter( &m_StartTime );
}

CFrameRate::~CFrameRate()
{
}

void CFrameRate::Wait()
{
	QueryPerformanceCounter( &m_NowTime );
	m_FrameTime =
		static_cast<double>(m_NowTime.QuadPart - m_StartTime.QuadPart) / 
		static_cast<double>(m_FreqTime.QuadPart);

	if( m_FrameTime < FRAME_TIME ){
		DWORD sleepTime = 
			static_cast<DWORD>((FRAME_TIME - m_FrameTime) * 1000.0);
		timeBeginPeriod(1);
		Sleep( sleepTime ); 
		timeEndPeriod(1); 

		return;
	}
	m_StartTime = m_NowTime;
}
