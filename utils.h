#ifndef UTILS_H
#define UTILS_H

int file_type_validation(int argc, char *argv);
char *check_for_comments_line(char *line);
int is_function_definition(const char *line);
void extract_function_name(const char *line, char *out_name);
int is_void_function(const char *name);

#endif