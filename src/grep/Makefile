CC = gcc
CFLAGS = -Wall -Wextra 

all: s21_grep

grep: grep.c
	$(CC) $(CFLAGS) -c grep.c

grep_flags: grep_flags.c
	$(CC) $(CFLAGS) -c grep_flags.c

string_work: string_work.c
	$(CC) $(CFLAGS) -c string_work.c

file_work: ../common/file_work.c
	$(CC) $(CFLAGS) -c ../common/file_work.c

s21_grep: grep grep_flags string_work file_work
	$(CC) -o s21_grep grep.o grep_flags.o string_work.o file_work.o

clean:
	rm -rf *.o

rebuild: clean all
	rm -rf *.o