#include "cat.h"

int main(int argc, char **argv) {
  FILE *res_file = fopen("res", "w");
  FILE *given_file = fopen(argv[argc - 1], "r");
  if ((res_file) && (given_file)) {
    overwriting(res_file, given_file);
    int *flags = flags_search(argv, argc - 1);
    if (flags[0]) {
      flag_bn(0);
    }
    if (flags[1]) {
      flag_e();
    }
    if (flags[2]) {
      flag_bn(1);
    }
    if (flags[3]) {
      flag_s();
    }
    if (flags[4]) {
      flag_t();
    }
    output(res_file);
    remove("res");
  } else {
    printf("%s", "ERROR!");
  }
}

int presence_b(char **flags, int len) {
  int flag_b = 0;
  for (int i = 1; i < len; i++) {
    if (!strcmp(flags[i], "-b")) {
      flag_b = 1;
    }
  }
  return flag_b;
}

int *flags_search(char **argv, int len) {
  static int flags[] = {0, 0, 0, 0,
                        0};  // 0 -> b; 1 -> e; 2 -> n; 3 -> s; 4 -> t
  for (int i = 1; i < len; i++) {
    if (!strcmp(argv[i], "-b") && (!flags[0])) {
      flags[0] = 1;
    } else if (!strcmp(argv[i], "-e") && (!flags[1])) {
      flags[1] = 1;
    } else if (!strcmp(argv[i], "-n") && (!presence_b(argv, len)) &&
               (!flags[2])) {
      flags[2] = 1;
    } else if (!strcmp(argv[i], "-s") && (!flags[3])) {
      flags[3] = 1;
    } else if (!strcmp(argv[i], "-t") && (!flags[4])) {
      flags[4] = 1;
    }
  }
  return flags;
}
