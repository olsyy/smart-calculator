CXX := g++
CXXFLAGS :=-Wall -Werror -Wextra -std=c++17
LDFLAGS := -lgtest -lgtest_main -pthread

VIEW_DIR := ./View
CONTROLLER_DIR := ./Controller
MODEL_DIR := ./Model
TESTS_DIR := ./Tests
BUILD_DIR := ./Build

SRC := $(wildcard $(VIEW_DIR)/*.cc) \
          $(wildcard $(CONTROLLER_DIR)/*.cc) \
          $(wildcard $(MODEL_DIR)/*.cc)
HEADER := $(wildcard $(VIEW_DIR)/*.h) \
          $(wildcard $(CONTROLLER_DIR)/*.h) \
          $(wildcard $(MODEL_DIR)/*.h)
UI := $(wildcard $(VIEW_DIR)/*.ui)
TESTS := $(wildcard $(TESTS_DIR)/*.cc)


UNAME :=$(shell uname -s)

ifeq ($(UNAME),Linux)
	LDFLAGS += -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	OPEN_CM=open
endif

.PHONY: all clean tests
all: clean install tests

install:
	mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

uninstall:
	rm -rf $(BUILD_DIR)

clean:
	rm -rf *.a *.o *.out *.gch *.gcno *.gcna *.gcda *.info *.tgz *.user s21_test latex html $(BUILD_DIR)

dvi:
	doxygen Doxyfile
	$(OPEN_CM) html/index.html

dist: clean
	mkdir dist_smartcalc/
	cp Makefile *.txt $(SRC) $(HEADER) $(UI) dist_smartcalc/
	tar -czvf s21_smartcalc.tgz dist_smartcalc/
	rm -rf dist_smartcalc/

tests: clean
	$(CXX) $(CXXFLAGS) -o s21_test $(MODEL_DIR)/*.cc $(TESTS) $(LDFLAGS)
	./s21_test

valgrind: tests
	valgrind --tool=memcheck --leak-check=yes --leak-check=full -s ./s21_test

style:
	cp ../materials/linters/.clang-format .
	clang-format -n $(SRC) $(HEADER)
	rm -rf .clang-format

edit_style:
	cp ../materials/linters/.clang-format .
	clang-format -i $(SRC) $(HEADER)
	rm -rf .clang-format
