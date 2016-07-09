#ifndef __LOG__
#define __LOG__


#define MAX_DESC_LEN 40 //length of the command description

//å~Q½ä»¤ç»~Sæ~^~Dä½~S
typedef int (*CmdProcFunc)(void *);
typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
	char         description[MAX_DESC_LEN];
}CMD_PROC;

//å~Q½ä»¤å¤~Dç~P~Få~G½æ~U°å®~Zä¹~I
//#define MOCK_FUNC(funcName) \
    int funcName(void){printf("  Enter "#funcName"!\n"); return 0;}

//MOCK_FUNC(ShowMeInfo);
//MOCK_FUNC(SetLogCtrl);
//MOCK_FUNC(TestBatch);
//MOCK_FUNC(TestEndianOper);


//å~Q½ä»¤è¡¨é¡¹å®~Oï¼~Lç~T¨äº~Nç®~@å~L~Vä¹¦å~F~Y
#define CMD_ENTRY(cmdStr, func, desc)     {cmdStr, func, desc}
#define CMD_ENTRY_END               {NULL,   NULL, NULL}

//define the max number of callback functions as 20
#define CMD_MAP_NUM     20  //(sizeof(gCmdMap)/sizeof(CMD_PROC)) - 1/*End*/

//å~Q½ä»¤è¡¨
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

int execute_log_func(void *);

#endif
