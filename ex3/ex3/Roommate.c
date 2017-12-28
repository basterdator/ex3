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
#include "main.h"

static int i;
extern int num_of_active_roomates;
extern int num_of_clothes_in_basket;
extern int NUM_OF_ROOMMATES;
extern int M;
extern HANDLE laundry_room;
extern HANDLE laundry_full;
extern HANDLE laundry_empty;
extern HANDLE write_to_file;
extern BOOL TimeIsUp;

static DWORD wait_res;
static BOOL release_res;

void ExitProcedure(roommate *p_roommate_list);
void LaundryRoomProcedure(roommate *p_current_roommate);
static void ReportErrorAndEndProgram();

DWORD WINAPI Roommate(LPVOID lpParam)
{



	roommate_thread *p_roommate_thread;
	if (NULL == lpParam)
	{
		return ROOMMATE_THREAD__CODE_NULL_PTR;
	}

	p_roommate_thread = (roommate_thread *)lpParam;
	roommate_thread roomate_params = *p_roommate_thread;
	int roommate_num = roomate_params.num_of_roomate;
	roommate *p_roommate_list = roomate_params.p_roomate_list;
	roommate *p_current_roommate = &p_roommate_list[roommate_num];

	While(TRUE);
	{
		Sleep((*p_current_roommate).T_i);

		// Up(write)
		wait_res = WaitForSingleObject(write_to_file, INFINITE);
		if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();

		// cretae the string to write to the file
		
		PrintToFile("Roommate", char *path);
		PrintToFile(roommate_num, char *path);
		PrintToFile("active\n", char *path);

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
				ExitProcedure(p_roommate_list);
			}
			else {

				// ExitProcedure()
				ExitProcedure(p_roommate_list);
			}

		}
		// LaundryRoomProcedure()
		LaundryRoomProcedure(p_current_roommate);

		// up(laundry_room)
		wait_res = WaitForSingleObject(laundry_room, INFINITE);
		if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();

		// If there are zero clothe in your basket:
		if ((*p_current_roommate).curret_clothes == 0)
		{
			// down(stuck_without_clothes)
			release_res = ReleaseSemaphore(
				(*p_current_roommate).NoClothes,
				1, 		/* Signal that exactly one cell was filled */
				NULL);
			if (release_res == FALSE) ReportErrorAndEndProgram();
		}

		// Repeat
	}
}





// exit_procedure():
void ExitProcedure(roommate *p_roommate_list) /* The exit procedure gets a pointer to the list of roomates
											  so it could release the semaphore of those who are stuck without clothes */
{
	roommate *current_roommate;

	//	num_of_active_roomates--
	num_of_active_roomates--;

	//	up(laundry_room)
	wait_res = WaitForSingleObject(laundry_room, INFINITE);
	if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();

	//	for(each roomate that has 0 clothes in his closet and has a nonzero amount of total clothes):
	for (i = 0;i < NUM_OF_ROOMMATES; i++)
	{
		current_roommate = &p_roommate_list[i];
		if ((*current_roommate).curret_clothes == 0 && (*current_roommate).total_clothes != 0)

		{
			//		up(stuck_without_clothes)
			wait_res = WaitForSingleObject((*current_roommate).NoClothes, INFINITE);
			if (wait_res != WAIT_OBJECT_0) ReportErrorAndEndProgram();
		}

	}
	//	return 0
	return ROOMMATE_THREAD__CODE_SUCCESS;


}



void LaundryRoomProcedure(roommate *p_current_roommate)
{
//	if there are M-1 Clothes in the basket
	if (num_of_clothes_in_basket == M)
	{
		//		up(basketfull)
		release_res = ReleaseSemaphore(
			laundry_full,
			1, 		/* Signal that exactly one cell was filled */
			NULL);
		if (release_res == FALSE) ReportErrorAndEndProgram();
		//		down(basketempty)
		release_res = ReleaseSemaphore(
			laundry_empty,
			1, 		/* Signal that exactly one cell was filled */
			NULL);
		if (release_res == FALSE) ReportErrorAndEndProgram();
		//		clothesinbasket = 0
		num_of_clothes_in_basket = 0;

	}
	else
	{
		num_of_clothes_in_basket++;
		(*p_current_roommate).curret_clothes--;
	}

}

static void ReportErrorAndEndProgram()
{
	printf("Encountered error, ending program. Last Error = 0x%x\n", GetLastError());
	exit(1);
}



