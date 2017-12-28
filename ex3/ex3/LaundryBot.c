/* ==============================================
Introduction to Systems Programming
Winter 2017-2018
TEL-AVIV UNIVERSITY
Exercise 3
Uri Cohen                 302825807
Anton Chaplianka          310224209
============================================== */

// Includes --------------------------------------------------------------------
#include <windows.h>
#include "LaundryBot.h"
#include "Timer.h"
#include "PrintToFile.h"
#include "main.h"


DWORD WINAPI LaundryBot(LPVOID lpParam)
{
	int i;
	extern int num_of_active_roomates;
	extern int num_of_clothes_in_basket;
	extern int NUM_OF_ROOMMATES;
	extern int M;
	extern HANDLE laundry_full;
	extern HANDLE laundry_empty;
	extern HANDLE write_to_file;

	static DWORD wait_res;
	static BOOL release_res;

	roommate *p_roomate_list;
	p_roomate_list = (roommate *)lpParam;

	While(TRUE);
	{
		// Down(laundry_full)

		release_res = ReleaseSemaphore(
			laundry_full,
			1, 		/* Signal that exactly one cell was filled */
			NULL);
		if (release_res == FALSE) ReportErrorAndEndProgram();


		// If time is up and the number of active threads is 1 - then the last roomate turns the robot off - so the robot shuts itself down.
		if (TimeIsUp == TRUE && num_of_active_roomates <= 1)
		{
			return LAUNDRYBOT_THREAD__CODE_SUCCESS;
		}

		// Else: the robot needs to complete it's operation
		// Writing in the log
		// Up(log)
		wait_res = WaitForSingleObject(write_to_file, INFINITE);
		if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();

		// write in the log file

		PrintToFile("bl33p bl00p, r0b0t 4ct1v3\n", 1);

		// Down(log)

		release_res = ReleaseMutex(write_to_file);
		if (release_res == FALSE) ReportErrorAndEndProgram();

		// Check each roomate whether he has zero clothes in his closet and he had a non zero num of clothes in the first place
		for (i = 0;i < NUM_OF_ROOMMATES; i++)
		{
			if (p_roomate_list[i].curret_clothes == 0 && p_roomate_list[i].total_clothes != 0)
			{
				printf("%d", p_roomate_list[i].curret_clothes);
				// empty the basket
				num_of_clothes_in_basket = 0;
				p_roomate_list[i].curret_clothes = p_roomate_list[i].total_clothes;  // fill up the closet
				release_res = ReleaseSemaphore(
					p_roomate_list[i].NoClothes,
					1, 		/* Signal that exactly one cell was filled */
					NULL);
				if (release_res == FALSE) { ReportErrorAndEndProgram(); }

			} 
			else
			{
				if (p_roomate_list[i].total_clothes != 0) 
				{
					p_roomate_list[i].curret_clothes = p_roomate_list[i].total_clothes;
				}
			}
		}

		// Up(laundry_empty)

		release_res = ReleaseSemaphore(
			laundry_empty,
			1, 		/* Signal that exactly one cell was filled */
			NULL);
		if (release_res == FALSE) ReportErrorAndEndProgram();
	}
	

}

static void ReportErrorAndEndProgram()
{
	printf("Encountered error, ending program. Last Error = 0x%x\n", GetLastError());
	exit(1);
}
