#include<stdio.h>
#include<string.h>
#include "utils.h"


int file_type_validation(int argc, char *argv)
{
    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s - no file - please enter the file for analyse\n", argv);
        return 1;
    }
    /*get_file_type*/
    const char *dot = strrchr(argv, '.');
    if (!dot || dot == argv) 
    {
        printf("No valid extension found\n");
        return 1;
    }
    if(strcmp(dot, ".c") != 0)
    {
        printf("Type: Unknown = %s\n",dot);
        return 1;
    }
    return 0;
}

char *check_for_comments_line(char *line) 
{
    char *single_comment = strstr(line, "//");
    char *multi_comment = strstr(line, "/*");

    if (!single_comment && !multi_comment)
    return NULL;

    if (single_comment && multi_comment) 
    {
        //printf("\n single command : %s , multi_comment : %s ,",single_comment,multi_comment);
        return (single_comment < multi_comment) ? single_comment : multi_comment;
    }

    return single_comment ? single_comment : multi_comment;
}