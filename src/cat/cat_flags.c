#include "cat_flags.h"

int flag_bn(int flag_n) {
  // do we need alignment?
  FILE *buf_file = fopen("buf", "w");
  FILE *res_file = fopen("res", "r");
  char str[256];
  int line_number = 0;
  while (fgets(str, 256, res_file) != NULL) {
    if (flag_n) {
      line_number += 1;
      fprintf(buf_file, "%d ", line_number);
    } else {
      if (strcmp(str, "\n")) {
        line_number += 1;
        fprintf(buf_file, "%d ", line_number);
      }
    }
    fprintf(buf_file, "%s", str);
  }
  get_data_from_buffer(res_file, buf_file);
  return 0;
}

int flag_e() {
  FILE *buf_file = fopen("buf", "w");
  FILE *res_file = fopen("res", "r");
  char str[256], buf_str[256] = "initial";
  while (fgets(str, 256, res_file) != NULL) {
    strcpy(buf_str, str);
    int length = strlen(buf_str);
    for (int i = 0; i < length; i++) {
      if (buf_str[i] == '\n') {
        buf_str[i] = '$';
        strcat(buf_str, "\n");
      }
    }
    fprintf(buf_file, "%s", buf_str);
  }
  get_data_from_buffer(res_file, buf_file);
  return 0;
}

int flag_s() {
  FILE *buf_file = fopen("buf", "w");
  FILE *res_file = fopen("res", "r");
  char str1[256], str2[256] = "initial";
  while (fgets(str1, 256, res_file) != NULL) {
    if (strcmp(str1, "\n") || strcmp(str2, "\n")) {
      fprintf(buf_file, "%s", str1);
      strcpy(str2, str1);
    }
  }
  get_data_from_buffer(res_file, buf_file);
  return 0;
}

int flag_t() {
  FILE *buf_file = fopen("buf", "w");
  FILE *res_file = fopen("res", "r");
  char str[256];
  while (fgets(str, 256, res_file) != NULL) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
      int number = str[i];
      if (number == 9)
        fprintf(buf_file, "%s", "^I");
      else
        fprintf(buf_file, "%c", str[i]);
    }
  }
  get_data_from_buffer(res_file, buf_file);
  return 0;
}
