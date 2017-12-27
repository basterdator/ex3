
// Roommate.h

#ifndef __ROOMMATE_H__
#define __ROOMMATE_H__


// Includes --------------------------------------------------------------------
#include <windows.h>


typedef struct roomate_s
{
	int time;
	int total_clothes;
	int curret_clothes;
	HANDLE NoClothes;
}roomate;

#endif // __ROOMMATE_H__
