/* ==============================================
Introduction to Systems Programming
Winter 2017-2018
TEL-AVIV UNIVERSITY
Exercise 3
Uri Cohen                 302825807
Anton Chaplianka          310224209
============================================== */

// Includes --------------------------------------------------------------------
#include "PrintToFile.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Constants  ------------------------------------------------------------------


int PrintToFile(char *p_msg, int index)  /* A function Which takes a string
												 and writes the string to the specified path, when the path is coded:
												 1 == The report file path
												 2 == The debug file path 
												 Any other integer returns an error */
{
	errno_t retval;
	FILE *p_stream;
	if (index == 1)
	{
		retval = fopen_s(&p_stream, p_report_file_path, "a");
		if (0 != retval)
		{
			printf("Failed to open file.\n");
			return FAILURE;
		}

		// Write lines
		retval = fputs(p_msg, p_stream);
		if (0 > retval)
		{
			printf("Failed to write to file.\n");
			// Don't return. Try and close the file first.
		}

		// Close file
		retval = fclose(p_stream);
		if (0 != retval)
		{
			printf("Failed to close file.\n");
			return FAILURE;
		}

		return SUCCESS;
	}
	if (index == 2)
	{
		retval = fopen_s(&p_stream, p_debug_file_path, "a");
		if (0 != retval)
		{
			printf("Failed to open file.\n");
			return FAILURE;
		}

		// Write lines
		retval = fputs(p_msg, p_stream);
		if (0 > retval)
		{
			printf("Failed to write to file.\n");
			// Don't return. Try and close the file first.
		}

		// Close file
		retval = fclose(p_stream);
		if (0 != retval)
		{
			printf("Failed to close file.\n");
			return FAILURE;
		}

		return SUCCESS;
	}
	else
	{
		// print error
		printf("Wrong file parameter.\n");
		return FAILURE;
	}
}