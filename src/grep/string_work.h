#ifndef SRC_GREP_STRING_WORK_H_
#define SRC_GREP_STRING_WORK_H_

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* to_lower(char* s);
int check_if_regex();
int matching_regex(char* template, char* str, int cflag);
char *without_hyphen(char *string);

#endif  // SRC_GREP_STRING_WORK_H_