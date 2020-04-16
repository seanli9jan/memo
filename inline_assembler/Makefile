CC = gcc

OPT_FILE_NAME = main
APP_FILES  = $(OPT_FILE_NAME).c
CFLAGS = -m32

all: compile_file

compile_file:
	$(CC) $(CFLAGS) $(APP_FILES) -o $(OPT_FILE_NAME)

clean:
	rm -f $(OPT_FILE_NAME)
