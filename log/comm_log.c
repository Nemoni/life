#include <stdio.h>

#include "comm_log.h"

// parse the input command to global varible
int parse_input_cmd(char *cmd)
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
