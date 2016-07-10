#include <stdio.h>
#include <string.h>

#include "cmd_line.h"
#include "comm_log.h"

int set_level_func(void *cmdMap);
int person_help_func(void *cmdMap);

extern unsigned int comm_level;

int person_func(void *cmdMap)
{
	//printf("person_func\n");

	CMD_PROC personCmdMap[CMD_MAP_NUM] = {
        CMD_ENTRY("set",       set_level_func, "set log level"),
        CMD_ENTRY("?",         person_help_func, "help command"),
        //CMD_ENTRY("TestBatch",        TestBatch),
        //CMD_ENTRY("TestEndian",       TestEndianOper),

        CMD_ENTRY_END
    };
    memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, personCmdMap, sizeof(gCmdMap));

    memcpy(pszCmdPrompt, "main.person>>", sizeof(pszCmdPrompt));

    execute_cmd_line(personCmdMap);
	
	//exit from person and recover the callback functions
	memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, cmdMap, sizeof(gCmdMap));
	
	memcpy(pszCmdPrompt, "main>>", sizeof(pszCmdPrompt));

	return 0;
}

int set_level_func(void *cmdMap)
{
	if (comm_set_level() < 0){
		printf("ERR; set_level_func failed!\n");
		return -1;
	}
	return 0;
}

int person_help_func(void *cmdMap)
{
	comm_help_func();

    return 0;
}
