CC=gcc

SRC_BACKEND_DIR = back
SRC_OBJ_DIR = $(SRC_BACKEND_DIR)/obj
SRC_IO_OBJ_DIR = $(SRC_BACKEND_DIR)/io_obj

TEST_DIR = test

SRC_BACKEND := $(shell find ${SRC_BACKEND_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_OBJ := $(shell find ${SRC_OBJ_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_IO_OBJ := $(shell find ${SRC_IO_OBJ_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_TEST := $(shell find ${TEST_DIR} -name "*.c" | sed -e 's/\.\///')

BUILD_DIR = o
BUILD_TEST_DIR = o_tests

GCOV_DIR = gcov_report

O_BACKEND := $(SRC_BACKEND:%.c=${BUILD_DIR}/%.o)
O_OBJ := $(SRC_OBJ:%.c=${BUILD_DIR}/%.o)
O_IO_OBJ := $(SRC_IO_OBJ:%.c=${BUILD_DIR}/%.o)
O_TEST := $(SRC_TEST:%.c=${BUILD_TEST_DIR}/%.o)

CFLAGS=-Wall -Wextra -Werror -std=c11
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: install test clean

QT_PROJECT_NAME = qt
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = SmartCalc-1.0

generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir -p ./$(QT_APP_FOLDER)
ifeq ($(shell uname), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo " Done."
	@echo "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

s21_3d_viewer.a: $(O_BACKEND) $(O_OBJ) $(O_IO_OBJ)
	@mkdir -p ${BUILD_DIR}
	@ar rc s21_3d_viewer.a $(O_BACKEND) $(O_OBJ) $(O_IO_OBJ)
	@ranlib s21_3d_viewer.a

${BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@


test: $(O_TEST) s21_3d_viewer.a
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o test.out
	@./test.out

test_manual: $(O) test_manual.c s21_3d_viewer.a
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o test.out
	@./test.out

${BUILD_TEST_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) -c $< -o $@


gcov_report: clean
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC_BACKEND) $(TEST_DIR)/*.c $(LDFLAGS) -o gcov_main
	@./gcov_main
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory gcov_report
	@rm -Rf *.gcda *.cov *.gcno *.info

ifeq ($(shell uname), Linux)
	@firefox gcov_report/index.html
else
	@open gcov_report/index.html
endif

TAR_DIR = ../SmartCalc_v1.0_v1.0_Archive

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp -R ./ $(TAR_DIR)/src
	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	rm -Rf $(TAR_DIR)

dvi:
	@doxygen Doxyfile
ifeq ($(shell uname), Linux)
	@firefox html/index.html
else
	@open html/index.html
endif

codestyle:
	@find ./ -type f -name "*.c" -o -name "*.h" -o -name "*.cpp" | xargs clang-format -n --style=google

clean:
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f s21_3d_viewer.a
	rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR) $(GCOV_DIR) gcov_main
	rm -rf *out *info
	rm -rf $(DOC_DIR) $(TAR_DIR) $(TAR_DIR).tgz html
	rm -rf $(QT_BUILD_FOLDER)
	rm -rf build-qt*
	rm -f $(TEST_DIR)/test_samples/write*

rebuild: clean all
