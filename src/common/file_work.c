#include "file_work.h"

void output() {
  char str[256];
  FILE *res_file = fopen("../common/res", "r");
  while (fgets(str, 256, res_file) != NULL) {
    printf("%s", str);
  }
  fclose(res_file);
  remove("../common/res");
}