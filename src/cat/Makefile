CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: s21_cat

cat_flags.o: cat_flags.c
	$(CC) $(CFLAGS) -c cat_flags.c

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c

file_work.o: file_work.c
	$(CC) $(CFLAGS) -c file_work.c

s21_cat: cat.o cat_flags.o file_work.o
	$(CC) -o s21_cat cat.o cat_flags.o file_work.o

clean:
	rm -rf *.o

rebuild: clean all
	rm -rf *.o