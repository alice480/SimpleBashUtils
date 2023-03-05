#include "grep.h"

int main(int argc, char **argv) {
  int count = flags_count(argv, argc - 1);
  if (count == 1) {
    single_flag(argc, argv);
  } else {
    several_flags(argc, argv);
  }
}

int single_flag(int argc, char **argv) {
  FILE *given_file;
  for (int i = 3; i < argc; i++) {
    if (fopen(argv[i], "r")) {
      given_file = fopen(argv[i], "r");
      char error = 0;
      if (!strcmp(argv[1], "-e")) {
        flag_e(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-i")) {
        flag_i(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-v")) {
        flag_v(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-c")) {
        flag_c(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-l")) {
        flag_l(argv[2], given_file, argv[i]);
      } else if (!strcmp(argv[1], "-n")) {
        flag_n(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-h")) {
        flag_h(argv[2], given_file);
      } else if (!strcmp(argv[1], "-s")) {
        flag_s(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-o")) {
        flag_o(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else if (!strcmp(argv[1], "-f")) {
        flag_f(argv[2], given_file, argv[i], (argc - 3 > 1));
      } else {
        printf("%s", "ERROR!\n");
        error = 1;
      }
      if (!error) {
        output();
      }
      fclose(given_file);
    } else {
      printf("%s", "ERROR!\n");
    }
  }
  return 0;
}

int several_flags(int argc, char **argv) {
  int *flags = flags_search(argv, argc);
  int count = separated_count(argv, argc);
  for (int i = count + 2; i < argc; i++) {
    if (!flags[10]) {
      int output = (argc - count - 2 > 1);
      int low = flags[1], denial = flags[2], lines_count = flags[3], 
          file_names = flags[4], numbers = flags[5], errors = flags[7], not_empty = flags[9];
      if (flags[6]) {
        output = 0;
      }
      universal_flag(argv[count + 1], argv[i], low, denial, lines_count, file_names, numbers, errors, not_empty, output);
    } else {
      printf("%s", "ERROR!\n");
    }
  }
  return 0;
}

int flags_count(char **argv, int len) {
  int end = 0, count = 0;
  for (int i = 1; i < len && !end; i++) {
    if ((strlen(argv[i]) >= 2) && (strstr(argv[i], "-")) && (!strstr(argv[i], "."))) {
      count += strlen(argv[i]) - 1;
    } else {
      end = 1;
    }
  }
  return count;
}

int separated_count(char **argv, int len) {
  int end = 0, count = 0;
  for (int i = 1; i < len && !end; i++) {
    if ((strlen(argv[i]) >= 2) && (strstr(argv[i], "-")) && (!strstr(argv[i], "."))) {
      count += 1;
    } else {
      end = 1;
    }
  }
  return count;
}

int *flags_search(char **argv, int argc) {
  // 0 -> e; 1 -> i; 2 -> v; 3 -> c; 4 -> l; 5 -> n; 6 -> h; 7 -> s; 8 -> f; 9 -> o; 10 -> error;
  static int flags[] = {0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0};
  int count = separated_count(argv, argc);
  for (int i = 1; i < count + 1 && !flags[10]; i++) {
    if ((check_conjoint(argv[i], "e") || check_separate(argv[i], "-e"))) {
      if (check_single(flags, 8)) {  
        flags[0] = 1;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "i") || check_separate(argv[i], "-i")) {
      if (!flags[0] && !flags[8]) {
        flags[1] = 1;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "v") || check_separate(argv[i], "-v")) {
      if (!flags[0] && !flags[8]) {
        flags[2] = 1;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "c") || check_separate(argv[i], "-c")) {
      if (!flags[0] && !flags[8]) {
        if (!flags[4]) {  // l absent
          flags[3] = 1, flags[5] = 0, flags[6] = 0, flags[9] = 0;
        }
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "l") || check_separate(argv[i], "-l")) {
      if (!flags[0] && !flags[8]) {
        flags[4] = 1, flags[3] = 0, flags[5] = 0, flags[6] = 0, flags[9] = 0;
      } else {
        flags[10] = 1;
      }
    } else if (check_conjoint(argv[i], "n") || check_separate(argv[i], "-n")) {
      if (!flags[0] && !flags[8]) {
        flags[5] = (!flags[3] && !flags[4]) ? 1 : 0;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "h") || check_separate(argv[i], "-h")) {
      if (!flags[0] && !flags[8]) {
        flags[6] = (!flags[3] && !flags[4]) ? 1 : 0;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "s") || check_separate(argv[i], "-s")) {
      if (!flags[0] && !flags[8]) {
        flags[7] = 1;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "f") || check_separate(argv[i], "-f")) {
      if (check_single(flags, 0)) {
        flags[8] = 1;
      } else {
        flags[10] = 1;
      }
    }
    if (check_conjoint(argv[i], "o") || check_separate(argv[i], "-o")) {
      if (!flags[0] && !flags[8]) {
        flags[9] = (!flags[3] && !flags[4]) ? 1 : 0;
      } else {
        flags[10] = 1;
      }
    }
  }
  return flags;
}

int check_conjoint(char *elem, char *flag) {
  return (strlen(elem) > 2) && (strstr(elem, flag));
}

int check_separate(char *elem, char *flag) {
  return (strlen(elem) == 2) && (!strcmp(elem, flag)); 
}

int check_single(int *flags, int number) {
  return !flags[1] * !flags[2] * !flags[3] * !flags[4] * !flags[5] * !flags[6] * !flags[7] * !flags[8] * !flags[number];
}