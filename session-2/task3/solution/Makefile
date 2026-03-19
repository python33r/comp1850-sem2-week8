CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = student
OBJS = main.o student.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# main.o: main.c student.h structure.h
# 	$(CC) $(CFLAGS) -c main.c

# student.o: student.c student.h structure.h
# 	$(CC) $(CFLAGS) -c student.c

%.o: %.c student.h structure.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
