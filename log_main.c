#include <stdio.h>

#include "cmd_line.h"
#include "comm_log.h"

int main_help_func(void *cmdMap)
{
	comm_help_func();
	return 0;
}

int main_set_func(void *cmdMap)
{
	comm_set_level();
	return 0;
}
