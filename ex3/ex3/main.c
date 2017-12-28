/* ==============================================
Introduction to Systems Programming
Winter 2017-2018
TEL-AVIV UNIVERSITY
Exercise 3
Uri Cohen                 302825807
Anton Chaplianka          310224209
============================================== */

// Includes --------------------------------------------------------------------
#include "Roommate.h"
#include "LaundryBot.h"
#include "PrintToFile.h"
#include "Timer.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Constants  ------------------------------------------------------------------


int main(int argc, char *argv[]) 
{

	roommate *roomates_array;
	int i;
	write_to_file = CreateMutex(
		NULL,   /* default security attributes */
		FALSE,	/* don't lock mutex immediately */
		NULL); /* un-named */
	if (write_to_file == NULL) 
	{ 
		CloseHandle(write_to_file);
		return -1;
	}

	laundry_room = CreateMutex(
		NULL,   /* default security attributes */
		FALSE,	/* don't lock mutex immediately */
		NULL); /* un-named */

	if (laundry_room == NULL)
	{
		CloseHandle(laundry_room);
		return -1;
	}

	laundry_full = CreateSemaphore(
		NULL,	/* Default security attributes */
		0,		/* Initial Count - all slots are empty */
		1,		/* Maximum Count */
		NULL); /* un-named */
	if (laundry_full == NULL)
	{
		CloseHandle(laundry_full);
		return -1;
	}

	laundry_empty = CreateSemaphore(
		NULL,	/* Default security attributes */
		0,		/* Initial Count - all slots are empty */
		1,		/* Maximum Count */
		NULL); /* un-named */
	if (laundry_empty == NULL)
	{
		CloseHandle(laundry_empty);
		return -1;
	}

	for (i = 0; i < NUM_OF_ROOMMATES; i++)
	{
		(*roomates_array).NoClothes = CreateSemaphore(
			NULL,	/* Default security attributes */
			0,		/* Initial Count - all slots are empty */
			1,		/* Maximum Count */
			NULL); /* un-named */
		if ((*roomates_array).NoClothes == NULL)
		{
			CloseHandle((*roomates_array).NoClothes);
			return -1;
		}

	}

}

//static void WashRoom()
//{
//
//
//}