#ifndef __CMD_LINE__
#define __CMD_LINE__

#define __READLINE_DEBUG //if install the readLine library then define this macro

#define MAX_DESC_LEN 40 //length of the command description

typedef int (*CmdProcFunc)(void);
typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
	char         description[MAX_DESC_LEN];
}CMD_PROC;

int funcName(void){printf("  Enter "#funcName"!\n"); return 0;}

#define CMD_ENTRY(cmdStr, func, desc)     {cmdStr, func, desc}
#define CMD_ENTRY_END               {NULL,   NULL, NULL}

//define the max number of callback functions as 20
#define CMD_MAP_NUM     20  //(sizeof(gCmdMap)/sizeof(CMD_PROC)) - 1/*End*/

// define the command name and callback function and description 
CMD_PROC gCmdMap[CMD_MAP_NUM];

#define MAX_PROMPT_LEN 20 //the promption length that display before input command
char pszCmdPrompt[MAX_PROMPT_LEN];

#define MAX_CMD_ARGC 5 // max number of args
#define MAX_ARG_LEN  20 // max length of one arg

unsigned int cmd_argc; //actual count of args
char cmd_argv[MAX_CMD_ARGC][MAX_ARG_LEN];

int execute_cmd_line(void);

#endif
