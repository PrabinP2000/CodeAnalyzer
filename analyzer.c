#include "analyzer.h"

int main(int argc, char *argv[])
{
    if(file_type_validation(argc,argv[1]))
    return 1;

    FILE *fp,*review;
    char line[MAX_LINE_LEN],*p;
    int line_number = 0;
    fp = fopen(argv[1],"r");
    if (!fp) 
    {
        perror("File not found");
        return 1;
    }
    else
    printf("\nfile for review : %s .\n",argv[1]);
    while (fgets(line, sizeof(line), fp)) 
    {
        line_number++;
        if (strlen(line) == 0) 
        continue;
        check_declaration(line, line_number);
        variable_usage(line);
        p = check_for_comments_line(line);
        if(p)
        {
            review = fopen("review.txt","a");
            if (!review) 
            perror("error in opening file");
            fprintf(review,"\n please remove the commented line if not needed : %d : %s  \n",line_number,p);
            fclose(review);
        }
    }
    fclose(fp);
    is_all_variable_used();
    return 0;

}
