#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "person.h"
#include "log_person.h"
#include "log.h"
#include "log_main.h"

extern int person_func(void *);
extern int main_help_func(void *);

extern CMD_PROC gCmdMap[];

int main()
{
    pid_t pid = 0;
//printf("main\n");    
    pid = fork();
    if (pid < 0){
        printf("error in fork!");
    }else if (pid == 0){
        //person();
        //printf("son\n");
        while (1){

        }
    }else {

    }


	CMD_PROC mainCmdMap[CMD_MAP_NUM] = {
    	CMD_ENTRY("person",       person_func, "enter person directory"),
    	CMD_ENTRY("?",            main_help_func, "help command"),
    	//CMD_ENTRY("TestBatch",        TestBatch),
    	//CMD_ENTRY("TestEndian",       TestEndianOper),

    	CMD_ENTRY_END
	};
	memset(gCmdMap, 0, sizeof(gCmdMap));
	memcpy(gCmdMap, mainCmdMap, sizeof(gCmdMap));

	memcpy(pszCmdPrompt, "main>>", sizeof(pszCmdPrompt));

	execute_log_func((void *)mainCmdMap);

	while (1){
        
	}      
}
