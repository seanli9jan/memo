CC = gcc

FEATURE ?= feature.mk
include $(FEATURE)

TOOL_DIR = tool
LIB_DIR  = lib

OPT_FILE_NAME = main
OBJ_FILE_NAME = func
DLL_FILE_NAME = _func

# objdump -p _libadd.so | grep SONAME
CC_SONAME = $(DLL_FILE_NAME).so.1
DLL_FILE  = $(DLL_FILE_NAME).so
CC_FILE   = $(OBJ_FILE_NAME).c

APP_FILES  = $(OPT_FILE_NAME).c
APP_FILES += $(OBJ_FILE_NAME).c

CREATE_DATA = create_data.py
DATA_FILE   = data
OBJ_FILE    = $(DATA_FILE).o
HEADER_FILE = $(DATA_FILE).h

CFLAGS = -I$(LIB_DIR)

ifeq ($(BOOL_LIB), y)
    CFLAGS += -DBOOL_LIB
endif

ifeq ($(BUILD_PY), y)
    OS := $(shell uname)
    ifeq ($(OS), Linux)
        # For Linux
        CFLAGS += -O3 -shared -Wl,-soname
    else ifeq ($(OS), Darwin)
        # For Mac
        CFLAGS += -O3 -shared -Wl,-install_name
    endif
else
    CFLAGS += -O3
endif

all: compile_file

ifeq ($(BUILD_PY), y)
compile_file:
	$(CC) $(CFLAGS),$(CC_SONAME) -o $(LIB_DIR)/$(DLL_FILE) -fPIC $(CC_FILE) -lm
else
convert_data:
	@python $(TOOL_DIR)/$(CREATE_DATA) $(TOOL_DIR)/$(DATA_FILE)
	@echo "python $(TOOL_DIR)/$(CREATE_DATA) $(TOOL_DIR)/$(DATA_FILE)"

create_header: convert_data
	@xxd -i $(TOOL_DIR)/$(OBJ_FILE) $(LIB_DIR)/$(HEADER_FILE)
	@echo "xxd -i $(TOOL_DIR)/$(OBJ_FILE) $(LIB_DIR)/$(HEADER_FILE)"

compile_file: create_header
	$(CC) $(CFLAGS) $(APP_FILES) -o $(OPT_FILE_NAME)
endif

clean:
	rm -f $(OPT_FILE_NAME) $(LIB_DIR)/$(DLL_FILE)
	rm -f $(TOOL_DIR)/$(OBJ_FILE) $(LIB_DIR)/$(HEADER_FILE)
	rm -f $(LIB_DIR)/*.pyc
