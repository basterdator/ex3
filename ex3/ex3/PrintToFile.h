
// PrintToFile.h

#ifndef __PRINTOFILE_H__
#define __PRINTOFILE_H__

#include "PrintToFile.h"
#include "Timer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Constants -------------------------------------------------------------------

#define SUCCESS ((int)(0))
#define FAILURE ((int)(-1))

static char p_report_file_path[] = "report.txt";
static char p_debug_file_path[] = "debug_log.txt";

// Function Declarations -------------------------------------------------------

int PrintToFile(char *StringToPrint, int index);

#endif // __PRINTOFILE_H__
