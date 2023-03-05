#include "grep_flags.h"

void record_file_name(int flag, FILE *file, char *file_name) {
  if (flag) {
    fprintf(file, "%s:", file_name);
  }
}

int check_condition(char *template, char *str, int cflag) {
  int flag = 0;
  char buf[strlen(template)];
  strcpy(buf, template);
  if (check_if_regex(buf) == 1) {
    if (strstr(str, buf)) {
      flag = 1;
    }
  } else if (check_if_regex(template) == 0) {
    if (!matching_regex(template, str, cflag)) {
      flag = 1;
    }
  }
  return flag;
}

int flag_e(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  while (fgets(str, 256, given_file) != NULL) {
    if (check_condition(template, str, REG_EXTENDED)) {
      record_file_name(output, res_file, file_name);
      fprintf(res_file, "%s", str);
    }
  }
  fclose(res_file);
  return 0;
}

int flag_i(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  while (fgets(str, 256, given_file) != NULL) {
    if (check_condition(to_lower(template), to_lower(str), REG_ICASE)) {
      record_file_name(output, res_file, file_name);
      fprintf(res_file, "%s", str);
    }
  }
  fclose(res_file);
  return 0;
}

int flag_v(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  while (fgets(str, 256, given_file) != NULL) {
    if (!check_condition(template, str, REG_EXTENDED)) {
      record_file_name(output, res_file, file_name);
      fprintf(res_file, "%s", str);
    }
  }
  fclose(res_file);
  return 0;
}

int flag_c(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  int count = 0;
  while (fgets(str, 256, given_file) != NULL) {
    if (check_condition(template, str, REG_EXTENDED)) {
      count += 1;
    }
  }
  record_file_name(output, res_file, file_name);
  fprintf(res_file, "%d\n", count);
  fclose(res_file);
  return 0;
}

int flag_l(char *template, FILE *given_file, char *file_name) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  char availability = 0;
  while ((fgets(str, 256, given_file) != NULL) && !(availability)) {
    if (!check_condition(template, str, REG_EXTENDED)) {
      availability += 1;
    }
  }
  if (availability) {
    fprintf(res_file, "%s", file_name);
  }
  fclose(res_file);
  return 0;
}

int flag_n(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  int line_number = 0;
  while (fgets(str, 256, given_file) != NULL) {
    line_number += 1;
    if (check_condition(template, str, REG_EXTENDED)) {
      record_file_name(output, res_file, file_name);
      fprintf(res_file, "%d:", line_number);
      fprintf(res_file, "%s", str);
    }
  }
  fclose(res_file);
  return 0;
}

int flag_s(char *template, FILE *given_file, char *file_name, int output) {
  if (given_file) {
    flag_e(template, given_file, file_name, output);
  }
  return 0;
}

int flag_o(char *template, FILE *given_file, char *file_name, int output) {
  char str[256];
  FILE *res_file = fopen("../common/res", "w");
  while (fgets(str, 256, given_file) != NULL) {
    char buf_str[256] = "";
    char *ptr = str;
    int temp_len = strlen(template);
    int entry = 0;
    while (check_condition(template, ptr, REG_EXTENDED)) {
      strncat(buf_str, template, strlen(template));
      strncat(buf_str, "\n", 2);
      entry = 1;
      ptr = strstr(ptr, template);
      ptr += temp_len;
    }
    if (entry) {
      record_file_name(output, res_file, file_name);
      fprintf(res_file, "%s", buf_str);
    }
  }
  fclose(res_file);
  return 0;
}

int flag_h(char *template, FILE *given_file) {
  flag_e(template, given_file, "", 0);
  return 0;
}

int flag_f(char *templates, FILE *given_file, char *file_name, int output) {
  char template[256], str[256];
  FILE *res_file = fopen("../common/res", "w");
  while (fgets(str, 256, given_file) != NULL) {
    FILE *temp_file = fopen(templates, "r");
    int recorded = 0;
    while (fgets(template, 256, temp_file) != NULL) {
      char buf[strlen(without_hyphen(template))];
      strcpy(buf, without_hyphen(template));
      if (check_condition(buf, str, REG_EXTENDED) && !recorded) {
        record_file_name(output, res_file, file_name);
        fprintf(res_file, "%s", str);
        recorded = 1;
      }
    }
    fclose(temp_file);
  }
  fclose(res_file);
  return 0;
}

int opposite_condition(char *template, char *str, int cflag, int denial) {
  int condition = check_condition(template, str, cflag);
  if (denial) {
    condition = !condition;
  }
  return condition;
}

int universal_flag(char *template, char *file_name, int low, int denial,
                   int lines_count, int file_names, int numbers, int errors,
                   int not_empty, int flag_output) {
  if (fopen(file_name, "r")) {
    FILE *given_file = fopen(file_name, "r");

    char str[256];
    FILE *res_file = fopen("../common/res", "w");
    int cflag = REG_EXTENDED;
    if (low) {
      strcpy(str, to_lower(str));
      strcpy(template, to_lower(template));
      cflag = REG_ICASE;
    }
    int count = 0, str_number = 0;
    while (fgets(str, 256, given_file) != NULL) {
      str_number += 1;
      if (opposite_condition(template, str, cflag, denial)) {
        count += 1;
        if (not_empty) {
          char *ptr = str;
          int temp_len = strlen(template);
          while (opposite_condition(template, ptr, cflag, denial)) {
            record_file_name(flag_output, res_file, file_name);
            if (numbers) {
              fprintf(res_file, "%d:", str_number);
            }
            fprintf(res_file, "%s\n", template);
            ptr = strstr(ptr, template);
            ptr += temp_len;
          }
        } else {
          if (!file_names) {
            record_file_name(flag_output, res_file, file_name);
            if (numbers) {
              fprintf(res_file, "%d:", str_number);
            }
            if (!lines_count) {
              fprintf(res_file, "%s", str);
            }
          }
        }
      }
    }
    if (lines_count) {
      fprintf(res_file, "%d", count);
    } else if (file_names && count) {
      fprintf(res_file, "%s", file_name);
    }
    fprintf(res_file, "%s", "\n");
    fclose(res_file);
    output();
  } else if (!errors) {
    printf("%s", "ERROR!\n");
  }
  return 0;
}