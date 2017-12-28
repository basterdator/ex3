
// Roommate.h

#ifndef __ROOMMATE_H__
#define __ROOMMATE_H__


// Includes --------------------------------------------------------------------
#include <windows.h>


typedef struct roommate_s
{
	int num_of_roomate;
	DWORD T_i;
	int total_clothes;
	int curret_clothes;
	HANDLE NoClothes;
}roommate;

typedef enum
{
	ROOMMATE_THREAD__CODE_SUCCESS,
	ROOMMATE_THREAD__CODE_NULL_PTR,
} ROOMMATE_THREAD__return_code_t;

#endif // __ROOMMATE_H__
