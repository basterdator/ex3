
// PrintToFile.h

#ifndef __PRINTOFILE_H__
#define __PRINTOFILE_H__

// Constants -------------------------------------------------------------------

#define SUCCESS ((int)(0))
#define FAILURE ((int)(-1))

static char *p_report_file_path;
static char *p_debug_file_path;

// Function Declarations -------------------------------------------------------

int PrintToFile(char *StringToPrint, int index);

#endif // __PRINTOFILE_H__
