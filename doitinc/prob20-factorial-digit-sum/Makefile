CC = gcc
CFLAGS = -Wall -Wextra -g -I../lib  # -I adds ../lib to the header search path 🔍

TARGET = factorial_sum
LIB_DIR = ../lib
OBJ = main.o $(LIB_DIR)/bigint.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c $(LIB_DIR)/bigint.h
	$(CC) $(CFLAGS) -c main.c

$(LIB_DIR)/bigint.o: $(LIB_DIR)/bigint.c $(LIB_DIR)/bigint.h
	$(CC) $(CFLAGS) -c $(LIB_DIR)/bigint.c -o $(LIB_DIR)/bigint.o

clean:
	rm -f $(TARGET) main.o $(LIB_DIR)/bigint.o
