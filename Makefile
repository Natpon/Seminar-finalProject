
CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = project_oldVersion.c E2E_test_oldVersion.c unit_test_oldVersion.c
OBJ = $(SRC:.c=.o)
TARGET = a.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(OBJ) $(TARGET)

.PHONY: all clean
