/*
* print command line
* need "-lreadline -ltermcap" when link
*/
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "log.h"
#include "comm_log.h"

#define __READLINE_DEBUG

extern int parse_input_cmd(char *cmd);

//返回gCmdMap中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
    return gCmdMap[dwCmdIndex].pszCmd;
}

//执行命令
static int ExecCmd(char *pszCmdLine, void *cmdMap)
{
    if(NULL == pszCmdLine)
        return -1; 
	if('\0' == *pszCmdLine){
		return 0; //if command is NULL do not print error
	}

	unsigned int cmdLen = 0;
    unsigned int dwCmdIndex = 0;

    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
		if(gCmdMap[dwCmdIndex].pszCmd!=NULL){
			cmdLen = strlen(gCmdMap[dwCmdIndex].pszCmd);
			if(!strncmp(pszCmdLine, gCmdMap[dwCmdIndex].pszCmd, cmdLen)){
				if (*(pszCmdLine+cmdLen) != ' ' && *(pszCmdLine+cmdLen) != '\0'){
					continue;
				}
				
				parse_input_cmd(pszCmdLine);
				break;
			}
		}
    }
    if(CMD_MAP_NUM == dwCmdIndex)
        return -1;
    gCmdMap[dwCmdIndex].fpCmd(cmdMap); //调用相应的函数

    return 0;
}


#ifdef __READLINE_DEBUG


//退出交互式调测器的命令(不区分大小写)
static const char *pszQuitCmd[] = {"Quit", "Exit", "End", "Bye", "Q", "E", "B"};
static const unsigned char ucQuitCmdNum = sizeof(pszQuitCmd) / sizeof(pszQuitCmd[0]);
static int IsUserQuitCmd(char *pszCmd)
{
    unsigned char ucQuitCmdIdx = 0;
    for(; ucQuitCmdIdx < ucQuitCmdNum; ucQuitCmdIdx++)
    {
        if(!strcasecmp(pszCmd, pszQuitCmd[ucQuitCmdIdx]))
            return 1;
    }

    return 0;
}

//剔除字符串首尾的空白字符(含空格)
static char *StripWhite(char *pszOrig)
{
    if(NULL == pszOrig)
        return "NUL";

    char *pszStripHead = pszOrig;
    while(isspace(*pszStripHead))
        pszStripHead++;

    if('\0' == *pszStripHead)
        return pszStripHead;

    char *pszStripTail = pszStripHead + strlen(pszStripHead) - 1;
    while(pszStripTail > pszStripHead && isspace(*pszStripTail))
        pszStripTail--;
    *(++pszStripTail) = '\0';

    return pszStripHead;
}

static char *pszLineRead = NULL;  //终端输入字符串
static char *pszStripLine = NULL; //剔除前端空格的输入字符串
char *ReadCmdLine()
{
     //若已分配命令行缓冲区，则将其释放
    if(pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }
    //读取用户输入的命令行
    pszLineRead = readline(pszCmdPrompt);

    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    pszStripLine = StripWhite(pszLineRead);
    if(pszStripLine && *pszStripLine)
        add_history(pszStripLine);

    return pszStripLine;
}

static char* CmdGenerator(const char *pszText, int dwState)
{
    static int dwListIdx = 0, dwTextLen = 0;
    if(!dwState)
    {
        dwListIdx = 0;
        dwTextLen = strlen(pszText);
    }

    //当输入字符串与命令列表中某命令部分匹配时，返回该命令字符串
    const char *pszName = NULL;
    while((pszName = GetCmdByIndex(dwListIdx)))
    {
        dwListIdx++;
        if(!strncmp (pszName, pszText, dwTextLen))
            return strdup(pszName);
    }

    return NULL;
}

static char** CmdCompletion (const char *pszText, int dwStart, int dwEnd)
{
    //rl_attempted_completion_over = 1;
    char **pMatches = NULL;
    if(0 == dwStart)
        pMatches = rl_completion_matches(pszText, CmdGenerator);

    return pMatches;
}

//初始化Tab键能补齐的Command函数
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}

#endif


int execute_log_func(void *cmdMap)
{
#ifndef __READLINE_DEBUG
    printf("Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!\n\n");
#else
//    printf("Note: Welcome to Interactive Command!\n");
//    printf("      Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();
    while(1)
    {//也可加入超时机制以免忘记退出
        char *pszCmdLine = ReadCmdLine();
        if(IsUserQuitCmd(pszCmdLine))
        {
			if(pszLineRead != NULL){
            	free(pszLineRead);
				pszLineRead = NULL;
			}
            break;
        }

        if (ExecCmd(pszCmdLine, cmdMap) < 0){
			printf("ERR: can't find command!");
		}
    }
#endif

    return 0;
}




