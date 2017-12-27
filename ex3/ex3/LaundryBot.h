
// LaundryBot.h

#ifndef __LAUNDRYBOT_H__
#define __LAUNDRYBOT_H__


// Includes --------------------------------------------------------------------
#include "Roommate.h"

typedef struct laundrybot_s
{
	roommate *p_roomate_list;
}bot;

typedef enum
{
	LAUNDRYBOT_THREAD__CODE_SUCCESS,
	LAUNDRYBOT_THREAD__CODE_NULL_PTR,
} LAUNDRYBOT_THREAD__return_code_t;

DWORD WINAPI LaundryBot(LPVOID lpParam);
static void ReportErrorAndEndProgram();



#endif // __LAUNDRYBOT_H__
