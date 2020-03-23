/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: vodden
 *
 * Created on February 22, 2020, 5:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * 
 */
//Functions to use later
char* readLine();
char **splitArgs(char *line,char *deli);
void executeCmds(char ** args);
void pipingCmds(char *line);

//main function
int main(int argc, char** argv) {
    char *line;
    //char **args;
    
    //our main loop for the terminal
    while(1){
        printf("Your Command>");
        line = readLine();
        pipingCmds(line);
       
    }
}


//How it will read the lines
char* readLine(){
    int position=0;
    char *buffer = malloc(sizeof(char)*100);
    int c;
    
    while(1){
        c = getchar();
        //getting the args into a string
        if(c==EOF || c=='\n'){
            buffer[position]='\0';
            return buffer;
        }
        else{
            buffer[position]= c;
        }
        
        position++;
    }
    
    
}


//This will split the string into individual args
char **splitArgs(char *line, char *deli){

    int size=100, position =0;
    char **tokens=malloc(size*sizeof(char*));
    char *token;
    token = strtok(line,deli);
    
    while(token!=NULL){
        tokens[position] =token;
        position++;
        token = strtok(NULL,deli);
    }
    tokens[position]=NULL;
    return tokens;
    
}
void pipingCmds(char* line){
    char **args1,**args2,*line1,*line2;
    line1 =malloc(sizeof(char*)*100);
    line2=malloc(sizeof(char*)*100);
    int i=0,j=0,myPipe[2];
    while(line[i]!='|'){
        line1[i]= line[i];
        i++;
    }
    line1[i]=(char)'\0';
    i++;

    while(line[i]!='\0'){
        line2[j]=line[i];
        i++;
        j++;
        }
    line2[j]='\0';
    
    
    args1= splitArgs(line1," ");
    args2=splitArgs(line2," ");
    pipe(myPipe);
    if (fork()==0){
        dup2(myPipe[1],STDOUT_FILENO);
        close(myPipe[0]);
        execvp(args1[0],args1);
    }else{
        dup2(myPipe[0],STDIN_FILENO);
        close(myPipe[1]); 
        execvp(args2[0],args2);
    }
    
    
    
    
}
