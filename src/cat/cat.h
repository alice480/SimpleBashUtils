#ifndef SRC_CAT_CAT_H_
#define SRC_CAT_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat_flags.h"

int presence_b(char **flags, int len);
int *flags_search(char **argv, int len);

#endif  // SRC_CAT_CAT_H_
