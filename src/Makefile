#Constants
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1
OFLAGS=-O2
LDFLAGS=-lgtest -pthread

#Coverage
GCOVFLAGS=--coverage
GCOV_DIR=gcov

#Directories
TEST_DIR=tests
MODEL_DIR=model
SRC_DIR=.
OBJ_DIR=obj
OBJ_DIR_GCOV=$(OBJ_DIR)/$(GCOV_DIR)
OBJ_DIR_TEST=$(OBJ_DIR)/$(TEST_DIR)
BUILD_DIR=build
INSTALL_DIR=install

#Files
SRCS_TEST=$(wildcard $(TEST_DIR)/s21_*.cc $(MODEL_DIR)/s21_*.cc)
OBJS_TEST=$(patsubst %.cc, $(OBJ_DIR_TEST)/%.o, $(notdir $(SRCS_TEST)))
OBJS_GCOV=$(patsubst %.cc, $(OBJ_DIR_GCOV)/%.o, $(notdir $(SRCS_TEST)))
CLANG_FILES=$(shell find $(SRC_DIR) \( -name "s21_*.cc" -o -name "s21_*.h" \) -print)

#Builds
PROGRAM=s21_3DViewer_v2
TEST=test
TEST_GCOV=$(TEST)_gcov
TEST_BUILD=$(TEST)_build
TEST_BUILD_GCOV=$(TEST_BUILD)_gcov
VPATH=$(TEST_DIR):$(MODEL_DIR)

#Docs
DOC=doc_3DViewer_v2

# Open command
OS := $(shell uname -s)
ifeq ($(OS), Linux)
	OPEN_CMD=./$(INSTALL_DIR)/$(PROGRAM)
endif
ifeq ($(OS), Darwin)
	OPEN_CMD=open $(INSTALL_DIR)/$(PROGRAM).app
endif

.PHONY: all $(TEST) $(TEST_BUILD) $(TEST_GCOV) $(TEST_BUILD_GCOV) build install uninstall gcov_report lcov_report dvi dist clean clean_gcda rebuild clang_n clang_i valgrind valgrind_mac

all: install

$(TEST): $(TEST_BUILD)
	./$@ || true

$(TEST_BUILD): $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(OFLAGS) -o $(TEST)

$(OBJ_DIR_TEST)/%.o: %.cc
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

$(TEST_GCOV): $(TEST_BUILD_GCOV)
	$(MAKE) clean_gcda
	./$@ || true

$(TEST_BUILD_GCOV): $(OBJS_GCOV)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST_GCOV)

$(OBJ_DIR_GCOV)/%.o: %.cc
	@mkdir -p $(OBJ_DIR_GCOV)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

build:
	@mkdir -p $(BUILD_DIR)
	cd ./$(BUILD_DIR)/ && qmake ../ && make

install: build
	@mkdir -p $(INSTALL_DIR)
	@cp $(BUILD_DIR)/$(PROGRAM) $(INSTALL_DIR)/$(PROGRAM)

uninstall:
	rm -rf $(INSTALL_DIR)

open:
	$(OPEN_CMD)

gcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter $(MODEL_DIR)/s21_\.\*
	open $(GCOV_DIR)/index.html

lcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	lcov --capture --directory $(SRC_DIR) --exclude "$(CURDIR)/tests/*" --output-file $(GCOV_DIR)/coverage.info --no-external
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
	open $(GCOV_DIR)/index.html

dvi:
	texi2dvi --clean --pdf $(DOC).texi
	open $(DOC).pdf

dist:
	mkdir -p $(PROGRAM)/src
	@cp s21_* Makefile $(PROGRAM)/src 2>/dev/null || true
	@cp -r model/ controller/ view/ utils/ thirdparty/ $(PROGRAM)/src 2>/dev/null || true
	tar cvzf $(PROGRAM).tgz $(PROGRAM)/
	rm -rf $(PROGRAM)/

clean:
	rm -rf $(OBJ_DIR) $(GCOV_DIR) $(BUILD_DIR) $(TEST) $(TEST_GCOV) $(DOC).pdf

clean_gcda:
	rm -rf $(OBJ_DIR)/*.gcda

rebuild: clean all

clang_n:
	clang-format -n --style=Google $(CLANG_FILES)

clang_i:
	clang-format -i --style=Google $(CLANG_FILES)

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

valgrind_mac: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST) | grep LEAK:
