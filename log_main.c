#include <stdio.h>

#include "cmd_line.h"
#include "comm_log.h"

int main_help_func()
{
	comm_help_func();
	return 0;
}

int main_set_func()
{
	comm_set_level();
	return 0;
}
