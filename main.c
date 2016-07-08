#include <stdio.h>
#include <unistd.h>

#include "person.h"

int main()
{
    pid_t pid = 0;
printf("main\n");    
    pid = fork();
    if (pid < 0){
        printf("error in fork!");
    }else if (pid == 0){
        //person();
        printf("son\n");
        while (1){

        }
    }else {

    }
	
	while (1){
        
	}      
}
