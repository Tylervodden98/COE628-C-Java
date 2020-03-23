/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tyler Vodden
 *
 * Created on February 1, 2020, 10:25 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * 
he */
int main(int argc, char** argv) 
{
    while(1)
    {
        char * cmd;
        char * temp;
        int stat;
        pid_t pid;

    
        fprintf(stderr, "Your Command> ");//prompt 
        
        int ch; 
        //initialize space
        temp = (char*)calloc(0, sizeof(char)); 
        cmd  = (char*)calloc(0, sizeof(char)); 

        int size = 0;
        int i = 0,  numArgs = 1, j=0, andFlag=0;
    /*----------------Command input and parsing-----------------------------*/
        //get the command 
        do 
        {
            size++;
            temp = realloc(cmd, size*sizeof(char));//increase size if new argument
            cmd = temp;
            ch = getchar();
            if (ch == '&') //if there is an &, set the flag, skip iteration
            {
                andFlag =1;
                continue;
            }
           
            cmd[size-1] = ch;  
        }
        while (ch  != '\n');
        
        

        //add termination characters and count size
        for (i = 0; i < size; i++)
        {
            if (cmd[i] == ' ' || cmd[i] == '\n')
            {
                cmd[i] = '\0';
                numArgs++;
              
            }

        }

        //store in an array of pointers 
        char * argPnt[numArgs];
        argPnt[0] = &cmd[0];   
        for (i =0; i < size-1; i++)
        {
            if (cmd[i] == '\0' && i < size)
            {
                j++;
                argPnt[j] = &cmd[i+1];
            }
        }
        argPnt[numArgs -1] = NULL;//null termination 
        
        //break loop if exit is entered 
        if (strcmp(argPnt[0], "exit\0") == 0) 
        {
            break;
        }

    /*-------------Forking Process-----------------------*/
        pid = fork();
        //pid is 0 so it's a child 
        if (pid == 0)
        {
             execvp(argPnt[0], argPnt);
             free(cmd);
      
        }
        else if (pid > 0)//it's a parent 
        {
            if (andFlag) //parent shouldn't wait for child to execute 
            {
   
                
                fprintf(stderr, "\n");
                fprintf(stderr, "(Parent will not wait for child)\n");
                fprintf(stderr, "Please expect to see output in your prompt\n");
                 
              
            }
            else //parent will wait for child 
            {
          
                
                pid = wait(&stat);
                free(cmd);
               
            }
        }
    }

    return (EXIT_SUCCESS);
    
}


