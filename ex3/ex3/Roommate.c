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
#include "Timer.h"

void ExitProcedure();

DWORD WINAPI Roommate(LPVOID lpParam)
{

	extern int num_of_active_roomates;
	extern HANDLE laundry_room;
	extern HANDLE laundry_full;
	extern HANDLE laundry_empty;
	extern HANDLE write_to_file;
	extern BOOL TimeIsUp;


	static DWORD wait_res;
	static BOOL release_res;

	roommate *p_roommate;
	if (NULL == lpParam)
	{
		return ROOMMATE_THREAD__CODE_NULL_PTR;
	}
	
	p_roommate = (roommate *)lpParam;

	While(TRUE);
	{
		Sleep((*p_roommate).T_i);

		// Up(write)
		wait_res = WaitForSingleObject(write_to_file, INFINITE);
		if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();

		// cretae the string to write to the file
		/// Add code here!!!
		// Write in the diary
		PrintToFile("Roommate Active\n", 1);

		// Down(write)
		release_res = ReleaseMutex(write_to_file);
		if (release_res == FALSE) ReportErrorAndEndProgram();

		// down(laundry_room)
		release_res = ReleaseMutex(laundry_room);
		if (release_res == FALSE) ReportErrorAndEndProgram();

		// If times up:
		if (TimeIsUp == TRUE)
		{
			// If the num of active roomates is 1 :
			if (num_of_active_roomates == 1)
			{
				// Up(laundry_full)
				release_res = ReleaseSemaphore(
					laundry_full,
					1, 		/* Signal that exactly one cell was filled */
					NULL);
				if (release_res == FALSE) ReportErrorAndEndProgram();
				// ExitProcedure()
				ExitProcedure();
			}

		}

			// else: 
				// ExitProcedure()
			// LaundryRoomProcedure()
		
		// up(laundry_room)

		// If there are zero clothe in your basket:
		// down(stuck_without_clothes)
		// Repeat

	}
	



		
}


void ExitProcedure()
{
	extern int num_of_active_roomates;
	//	num_of_active_roomates--
	num_of_active_roomates--;

	//	up(laundry_room)

	//	for(each roomate that has 0 clothes in his closet and has a nonzero amount of clothes):
	//		up(stuck_without_clothes)
	//	return 0

}




// LaundryRoomProcedure();
//	if there are M-1 Clothes in the basket
//		up(basketfull)
//		down(basketempty)
//		clothesinbasket = 0
//		up(laundryroom)
//	else:
//		clothesinbasket++
//		clothesinclostet--

// exit_procedure():



