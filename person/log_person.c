#include <stdio.h>
#include <string.h>

#include "cmd_line.h"
#include "comm_log.h"

int set_level_func(void);
int person_help_func(void);

extern unsigned int comm_level;

int person_func()
{
    CMD_PROC tmpCmdMap[CMD_MAP_NUM];
	CMD_PROC personCmdMap[CMD_MAP_NUM] = {
        CMD_ENTRY("set",       set_level_func,   "set log level"),
        CMD_ENTRY("?",         person_help_func, "help command"),
        CMD_ENTRY_END
    };
    
    //copy the current command map to the temp map
    memset(tmpCmdMap, 0, sizeof(gCmdMap));
    memcpy(tmpCmdMap, gCmdMap, sizeof(gCmdMap));

    //copy the person command map to the global map
    memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, personCmdMap, sizeof(gCmdMap));

    memcpy(pszCmdPrompt, "main.person>> ", sizeof(pszCmdPrompt));

    //go into person mode
    execute_cmd_line();
	
	//exit from person and recover the command map
	memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, tmpCmdMap, sizeof(gCmdMap));
	
	memcpy(pszCmdPrompt, "main>> ", sizeof(pszCmdPrompt));

	return 0;
}

int set_level_func()
{
	if (comm_set_level() < 0){
		printf("ERR: set_level_func failed!\n");
		return -1;
	}
	return 0;
}

int person_help_func()
{
	comm_help_func();

    return 0;
}
