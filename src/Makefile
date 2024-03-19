CC = g++
CFLAGS =-Wall -Werror -Wextra -lstdc++ -std=c++17
GTEST= -lgtest

VIEW_DIR = view/
APP_DIR = Application
TEST_DIR = s21_tests/
MOD_DIR = model/
CONTR_DIR = controller/

TEST =  $(wildcard $(TEST_DIR)*.cc) $(wildcard $(MOD_DIR)*.cc) 

OS = $(shell uname)

ifeq ($(OS), Darwin)
	QMAKE = qmake
	APP_NAME = calc_2.app
else
	QMAKE = qmake
	APP_NAME = calc_2
endif

all: install

install: 
	[ -d $(APP_DIR) ] || mkdir -p $(APP_DIR)
	cd $(APP_DIR) && qmake ../view
	make -C ./$(APP_DIR)

open: install
	$(APP_DIR)/./$(APP_NAME)

uninstall:
	rm -rf $(APP_DIR) || true

dvi:
	open ../README.md

dist: uninstall clean
	cd ../ && tar -czvf SmartCalc_v2.tar src

tests: 
	g++ -Wall -Werror -Wextra -g model/polish_notation.cpp model/polish_notation.h -c
	g++ -Wall -Werror -Wextra -g test/test.cpp model/polish_notation.h -c
	g++ -Wall -Werror -Wextra -g test.o polish_notation.o -o res  -lgtest
	./res

clean: uninstall
	@ rm *.tgz || true
	@ rm -rf tests || true
	@ rm -rf *.info *.gcda *.gcno *.gcov *.gch *.dSYM || true
	rm -rf *.o res model/*.h.gch view/Makefile
