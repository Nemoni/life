#include <stdio.h>
#include <string.h>

#include "cmd_line.h"
#include "comm_log.h"

int comm_set_level()
{
    int level_value = 0;          
	
	if (1 == cmd_argc){
		goto usage;
	}

	if (!strncmp(cmd_argv[1], "set", strlen(cmd_argv[1]))){
		if (sscanf(cmd_argv[2], "%x", &level_value) != 1){
			printf("ERR: get the value of level failed! cmd_argv[2]:%s\n", cmd_argv[2]);
			return -1;
		}
		comm_level = level_value;
	}else{
        if (sscanf(cmd_argv[1], "%x", &level_value) != 1){
            printf("ERR: get the value of level failed! cmd_argv[1]:%s\n", cmd_argv[1]);
            return -1;
        }
		comm_level |= level_value;
	}
	printf("Success: comm_level = 0x%08x\n", comm_level);

    //print input argv and argc for debug
    LOG(LEVEL_DEBUG, "cmd_argc:%d\n", cmd_argc);
    int i = 0;
    while (i < cmd_argc){
        LOG(LEVEL_DEBUG, "cmd_argv[%d]:%s\n", i, cmd_argv[i]);
        i++;
    }
	return 0;
usage:
	printf("Syntax: set [set] <level>\n");
	printf("comm_level = 0x%08x\n", comm_level);
	printf("	set  :  set the common log level\n"
		   "	[set]:  mean & nor |\n"    
		   "	level: \n   \
		#define LEVEL_DEBUG 0x00000001\n   \
		#define LEVEL_INFO  0x00000002\n   \
		#define LEVEL_WARN  0x00000004\n   \
		#define LEVEL_ERR   0x00000008\n   \
		#define LEVEL_ALL   0x00000010\n");
    
    return 0;
}

int comm_help_func()
{
    unsigned int dwCmdIndex = 0;

    printf("\n");
    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if(gCmdMap[dwCmdIndex].pszCmd!=NULL && gCmdMap[dwCmdIndex].description!=NULL){
            printf("%-20s  %-s\n", gCmdMap[dwCmdIndex].pszCmd, gCmdMap[dwCmdIndex].description);
        }
    }
    printf("%-20s  %-s\n", "q", "quit\n");
    printf("\n");

    return 0;
}
