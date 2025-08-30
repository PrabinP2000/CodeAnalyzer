#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "utils.h"

#define MAX_VARS 100

typedef struct 
{
    char name[50];
    int declared_line;
    int used;
} Variable;

Variable vars[MAX_VARS];
int var_count = 0;

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

void add_variable(const char *name, int line_num) 
{
    int i;
    for ( i = 0; i < var_count; i++) 
    {
        if (strcmp(vars[i].name, name) == 0) 
        {
            printf("\n variable is already declared\n");
            return;
        }
    }
    if (var_count < MAX_VARS)
     {
        strncpy(vars[var_count].name, name, 49);
        vars[var_count].declared_line = line_num;
        vars[var_count].used = 0;
        var_count++;
    }
#if debug_checkvariable    
    printf("\r\n variables : \r\n");
    for(i=0;i<var_count;i++)
        printf("\n %d = %s \n",i+1,vars[i].name);
#endif
}

void variable_usage(const char *line) 
{
    for (int i = 0; i < var_count; i++) 
    {
        if ((strstr(line, vars[i].name)))
        {
            if((strstr(line, "(")) && (strstr(line,",")))
            printf("\r\n variable_usage 111 \r\n");
            //vars[i].used = 1;
        }
    }
}

void is_all_variable_used()
{
    printf("\n is_all_variable_used \n");
    for (int i = 0; i < var_count; i++)
    {
        printf("\n 1 is_all_variable_used \n");
        if(vars[i].used != 1)
        {
            printf("\n 2 is_all_variable_used \n");
            FILE *fp;
            fp = fopen("review.txt","a");
            if (!fp) 
            perror("error in opening file");
            fprintf(fp,"\n  Variable %s not used \n",vars[i].name);
            fclose(fp);
        }
    }
}

#if 0
void check_declaration(char *line, int line_num) 
{
    const char *types[] = {"int", "float", "double", "char", "long", "short"};
    int num_types = 6;
 
    for (int i = 0; i < num_types; i++) 
    {
        char pattern[20];
        snprintf(pattern, sizeof(pattern), "%s ", types[i]);
 
        char *pos = strstr(line, pattern);
        if (pos && !strstr(line, "(")) 
        { // exclude function declarations
            pos += strlen(pattern);
 
            // Get variable name (until = , or ;)
            char varname[50] = {0};
            int j = 0;
            while (*pos && *pos != '=' && *pos != ',' && *pos != ';' && !isspace(*pos)) 
            {
                varname[j++] = *pos;
                pos++;
            }
            varname[j] = '\0';
 
            if (strlen(varname) > 0) 
            {
                add_variable(varname, line_num);
            }
        }
    }
}
#endif
void check_declaration(char *line, int line_num) 
{
    const char *types[] = {"int", "float", "double", "char", "long", "short"};
    int num_types = 6;

    for (int i = 0; i < num_types; i++) 
    {
        char pattern[20];
        snprintf(pattern, sizeof(pattern), "%s ", types[i]);

        char *pos = strstr(line, pattern);
        if (pos && !strstr(line, "(")) 
        { // Exclude function declarations
            pos += strlen(pattern);

            // Process until semicolon
            char *end = strchr(pos, ';');
            if (!end) continue;

            char declaration[256] = {0};
            strncpy(declaration, pos, end - pos);
            declaration[end - pos] = '\0';

            // Tokenize by comma to get each variable
            char *token = strtok(declaration, ",");
            while (token) 
            {
                // Remove leading/trailing whitespace
                while (isspace(*token)) token++;

                // Copy variable name (up to '=' or end)
                char varname[50] = {0};
                int j = 0;
                while (*token && *token != '=' && !isspace(*token)) 
                {
                    varname[j++] = *token;
                    token++;
                }
                varname[j] = '\0';

                if (strlen(varname) > 0) 
                {
                    add_variable(varname, line_num);
                }

                token = strtok(NULL, ",");
            }
        }
    }
}