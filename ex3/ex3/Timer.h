#ifndef __TIMER_THREAD_H__
#define __TIMER_THREAD_H__

#include <windows.h>

/*
* A type for thread return codes
*/

typedef enum
{
	TIMER_THREAD__CODE_SUCCESS,
	TIMER_THREAD__CODE_NULL_PTR,
} TIMER_THREAD__return_code_t;

static BOOL TimeIsUp = FALSE;

DWORD WINAPI Timer(LPVOID lpParam);

#endif // __TIMER_THREAD_H__
