APP_NAME = geometry
TEST_NAME = test
LIB_NAME = libgeometry

CC = gcc

CFLAGS = -Wall -Wextra
CFLAGS_TEST = -Isrc -MMD -Ithirdparty
CPPFLAGS = -I src -MP -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

LDLIBS = -lm

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
TEST_OBJ_PATH = $(OBJ_DIR)/$(TEST_DIR)

SRC_EXT = c
APP_RUN = $(BIN_DIR)/./$(APP_NAME)
TEST_CHECK = $(BIN_DIR)/./$(TEST_NAME)

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CFLAGS_TEST) $< -o $@

.PHONY: test
test: $(TEST_PATH)

$(TEST_PATH): $(TEST_OBJ_PATH)/main.o $(TEST_OBJ_PATH)/circle_test.o $(LIB_OBJECTS)
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $@ $^ -lm
	
$(OBJ)/$(TEST_DIR)/%.o: $(TEST_DIR)/main.c $(TEST_DIR)/circle_test.c $(LIB_OBJECTS)
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -c -o $@ $< -lm

.PHONY: clean
clean:
	rm -f $(APP_PATH) $(TEST_PATH) $(LIB_PATH) 
	rm -rf $(DEPS) $(APP_OBJECTS) $(LIB_OBJECTS)
	rm -rf $(TEST_OBJ_PATH)/*.*
	
.PHONY: run
run: $(APP_RUN)
	$(APP_RUN)
	
.PHONY: rtest
rtest: $(TEST_CHECK)
	$(TEST_CHECK)
	
.PHONY: start
start:
	make clean
	make
	make test
	make rtest