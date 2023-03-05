#include "string_work.h"

char *to_lower(char *s) {
  for (char *p = s; *p; p++) *p = tolower(*p);
  return s;
}

int check_if_regex(char *template) {
  regex_t regex;
  int reg_expr = -1;
  if (!strstr(template, "[") && !strstr(template, "]") &&
      !strstr(template, "^") && !strstr(template, "$")) {
    reg_expr = 1;  // if usial string
  } else if (!regcomp(&regex, template, REG_EXTENDED)) {
    reg_expr = 0;  // if regular expression
    regfree(&regex);
  }
  return reg_expr;
}

int matching_regex(char *template, char *str, int cflag) {
  regex_t regex;
  regcomp(&regex, template, cflag);
  if (!strstr(template, "[") && !strstr(template, "]")) {
    char buf_str[256] = "[";
    strncat(buf_str, template, strlen(template));
    strcpy(template, buf_str);
    strncat(template, "]", 2);
  }
  int result = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  return result;
}

char *without_hyphen(char* string) {
  char buf[strlen(string)];
  if (strstr(string, "\n")) {
    strncpy(buf, string, strlen(string) - 1);
    string = buf;
  }
  return string;
}