CC = gcc

CFLAGS = -Wall -Wextra -g

TARGET = dedit

SRC = main.c editor.c ui.c

TEST_TARGET = test

TEST_SRC = tests/test_runner.c tests/test_editor.c editor.c


all:
	$(CC) $(CFLAGS) $(SRC) -lncurses -o $(TARGET)


test:
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)
	./$(TEST_TARGET)


clean:
	rm -f $(TARGET) $(TEST_TARGET)