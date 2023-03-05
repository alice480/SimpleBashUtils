#include "file_work.h"

void overwriting(FILE *res_file, FILE *given_file) {
  char str[256];
  while (fgets(str, 256, given_file) != NULL) {
    fprintf(res_file, "%s", str);
  }
  fclose(given_file);
  fclose(res_file);
}

void get_data_from_buffer(FILE *res_file, FILE *buf_file) {
  fclose(res_file);
  fclose(buf_file);
  res_file = fopen("res", "w");
  buf_file = fopen("buf", "r");
  overwriting(res_file, buf_file);
  remove("buf");
}

void output() {
  char str[256];
  FILE *res_file = fopen("res", "r");
  while (fgets(str, 256, res_file) != NULL) {
    printf("%s", str);
  }
  fclose(res_file);
}
