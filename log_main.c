#include <stdio.h>

#include "log.h"

int main_help_func(void *cmdMap)
{
	CMD_PROC (*pCmdMap)[CMD_MAP_NUM] = cmdMap; 
	unsigned int dwCmdIndex = 0;

	printf("\n");
    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if((*pCmdMap)[dwCmdIndex].pszCmd != NULL){
			printf("%s\n", gCmdMap[dwCmdIndex].pszCmd);
		}
    }
	printf("q\n");
	printf("\n");

	return 0;
}
