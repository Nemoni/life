#include <stdio.h>
#include <string.h>

#include "log.h"

int set_level_func(void *);

int person_func(void *cmdMap)
{
	printf("person_func\n");

	CMD_PROC personCmdMap[CMD_MAP_NUM] = {
        CMD_ENTRY("set",       set_level_func),
        //CMD_ENTRY("SetLogCtrl",       SetLogCtrl),
        //CMD_ENTRY("TestBatch",        TestBatch),
        //CMD_ENTRY("TestEndian",       TestEndianOper),

        CMD_ENTRY_END
    };
    memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, personCmdMap, sizeof(gCmdMap));

    memcpy(pszCmdPrompt, "main.person>>", sizeof(pszCmdPrompt));

    execute_log_func(personCmdMap);
	
	//exit from person and recover the callback functions
	memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, cmdMap, sizeof(gCmdMap));
	
	memcpy(pszCmdPrompt, "main>>", sizeof(pszCmdPrompt));

	return 0;
}

int set_level_func(void *cmdMap)
{
	printf("set_level_func\n");
	
	return 0;
}
