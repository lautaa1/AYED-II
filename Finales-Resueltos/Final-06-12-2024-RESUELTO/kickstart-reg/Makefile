CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = main.c plist.c elem.c plist_helpers.c
OBJECTS = $(SOURCES:.c=.o)
TESTFILES = $(shell ls input)
TARGET = listload

.PHONY: clean
.PHONY: all
.PHONY: testload
.PHONY: testcase
.PHONY: vtestcase
.PHONY: test
.PHONY: valgrind

all: $(TARGET)
testcases: testcase1 testcase2 testcase3 testcase4 testcase5
testload: $(TESTFILES)

test: testload testcase
valgrind: $(TESTFILES:.in=.val) vtestcase

testcase1: $(TARGET)
	@echo "\e[1;37mTesting $@: easy ...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-easy-005.in
	@echo "\n\n"

testcase2: $(TARGET)
	@echo "\e[1;37mTesting $@: only left elements...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-left-005.in
	@echo "\n\n"

testcase3: $(TARGET)
	@echo "\e[1;37mTesting $@: only right elements...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-right-005.in	@echo "\n\n"

testcase4: $(TARGET)
	@echo "\e[1;37mTesting $@: with negative pivot...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-negative-015.in
	@echo "\n\n"

testcase5: $(TARGET)
	@echo "\e[1;37mTesting $@: large list...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-100.in
	@echo "\n\n"

%.in: $(TARGET)
	@echo "\e[1;37mTesting $*...\e[0m\e[0;37m\n"
	./$(TARGET) input/$*.in
	@echo "\n\n"

%.val: $(TARGET)
	@echo "\e[1;37mTesting $*...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/$*.in
	@echo "\n\n"

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
