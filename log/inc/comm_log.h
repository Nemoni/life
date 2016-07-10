#ifndef __COMM_LOG__
#define __COMM_LOG__

#define MAX_CMD_ARGC 5 // max number of args
#define MAX_ARG_LEN  20 // max length of one arg


unsigned int cmd_argc; //actual count of args
char cmd_argv[MAX_CMD_ARGC][MAX_ARG_LEN];

unsigned int comm_level;

#define LEVEL_DEBUG 0x00000001
#define LEVEL_INFO  0x00000002
#define LEVEL_WARN  0x00000004
#define LEVEL_ERR   0x00000008
#define LEVEL_ALL   0x00000010


#define LOG(level, format, ...)                  \
	if (level & comm_level){                     \
		fprintf (stderr, "[func:%s,line:%d] "format, __FUNCTION__, __LINE__, ## __VA_ARGS__);\
	}

int comm_set_level();
int comm_help_func();

#endif
