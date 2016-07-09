#include <stdio.h>
#include <string.h>

#include "log.h"
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

    execute_log_func(personCmdMap);
	
	//exit from person and recover the callback functions
	memset(gCmdMap, 0, sizeof(gCmdMap));
    memcpy(gCmdMap, cmdMap, sizeof(gCmdMap));
	
	memcpy(pszCmdPrompt, "main>>", sizeof(pszCmdPrompt));

	return 0;
}

int set_level_func(void *cmdMap)
{
	//printf("set_level_func\n");
	comm_level = 1;	
	LOG(LEVEL_DEBUG, "no arg\n");
	
	LOG(LEVEL_DEBUG, "cmd_argc:%d\n", cmd_argc);

	int i = 0;
	while (i < cmd_argc){
		LOG(LEVEL_DEBUG, "%s ", cmd_argv[i]);
		//printf("%s, ", cmd_argv[i]);	
		i++;
	}
	LOG(LEVEL_DEBUG, "\n");
	
	return 0;
}

int person_help_func(void *cmdMap)
{
	CMD_PROC (*pCmdMap)[CMD_MAP_NUM] = cmdMap;
    unsigned int dwCmdIndex = 0;

    printf("\n");
    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if((*pCmdMap)[dwCmdIndex].pszCmd!=NULL && gCmdMap[dwCmdIndex].description!=NULL){
            printf("%-20s  %-s\n", gCmdMap[dwCmdIndex].pszCmd, gCmdMap[dwCmdIndex].description);
        }
    }
    printf("%-20s  %-s\n", "q", "quit\n");
    printf("\n");

    return 0;
}
