/*
* print command line
* need "-lreadline -ltermcap" when link
*/
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "cmd_line.h"
#include "comm_log.h"

#define __READLINE_DEBUG


// parse the input command to global varible
static int parse_input_cmd(char *cmd)
{
    char *p = NULL;
    char *head = NULL;
    unsigned int arg_len = 0;

    cmd_argc = 0;
    memset(cmd_argv, 0, sizeof(cmd_argv));
    p = cmd;

    while (*p != '\0'){
        if (' ' == *p){
            p++;
            continue;
        }
        head = p;
        while (*p!=' ' && *p!='\0'){
            arg_len++;
            if (arg_len == MAX_ARG_LEN){
                return -1;
            }
            p++;

        }
        strncpy(cmd_argv[cmd_argc], head, arg_len);
        arg_len = 0;

        cmd_argc++;
        if (cmd_argc == MAX_CMD_ARGC){
            return -1; // reach the max count of command
        }
    }

    return 0;
}

static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
    return gCmdMap[dwCmdIndex].pszCmd;
}

// get the input string and involve the callback function
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
    gCmdMap[dwCmdIndex].fpCmd(cmdMap);

    return 0;
}


#ifdef __READLINE_DEBUG


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

static char *pszLineRead = NULL;  // the string user input
static char *pszStripLine = NULL; // the string after get rid of the space
char *ReadCmdLine()
{
    if(pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }
	// get the input string and set prompt as well
    pszLineRead = readline(pszCmdPrompt);

	// git rid of the space at head and tail
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

	// compare input string pszText with global structure command map
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

// set this for auto-completion when input tab key
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}

#endif


int execute_cmd_line(void *cmdMap)
{
#ifndef __READLINE_DEBUG
    printf("Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!\n\n");
#else
//    printf("Note: Welcome to Interactive Command!\n");
//    printf("      Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();
    while(1)
    {
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
			printf("ERR: can't find command!\n");
		}
    }
#endif

    return 0;
}




