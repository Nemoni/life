#ifndef __LOG__
#define __LOG__


#define MAX_DESC_LEN 40 //length of the command description

typedef int (*CmdProcFunc)(void *);
typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
	char         description[MAX_DESC_LEN];
}CMD_PROC;

//#define MOCK_FUNC(funcName) \
    int funcName(void){printf("  Enter "#funcName"!\n"); return 0;}

//MOCK_FUNC(ShowMeInfo);
//MOCK_FUNC(SetLogCtrl);
//MOCK_FUNC(TestBatch);
//MOCK_FUNC(TestEndianOper);


#define CMD_ENTRY(cmdStr, func, desc)     {cmdStr, func, desc}
#define CMD_ENTRY_END               {NULL,   NULL, NULL}

//define the max number of callback functions as 20
#define CMD_MAP_NUM     20  //(sizeof(gCmdMap)/sizeof(CMD_PROC)) - 1/*End*/

// define the command name and callback function and description 
CMD_PROC gCmdMap[CMD_MAP_NUM];
/* = {
    CMD_ENTRY("person",       person_func),
    CMD_ENTRY("SetLogCtrl",       SetLogCtrl),
    CMD_ENTRY("TestBatch",        TestBatch),
    CMD_ENTRY("TestEndian",       TestEndianOper),

    CMD_ENTRY_END
};*/

#define MAX_PROMPT_LEN 20 //the promption length that display before input command
char pszCmdPrompt[MAX_PROMPT_LEN];

int execute_cmd_line(void *);

#endif
