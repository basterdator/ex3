
// Roommate.h

#ifndef __ROOMMATE_H__
#define __ROOMMATE_H__


// Includes --------------------------------------------------------------------
#include <windows.h>


typedef struct roommate_s
{
	int time;
	int total_clothes;
	int curret_clothes;
	HANDLE NoClothes;
}roommate;

#endif // __ROOMMATE_H__
