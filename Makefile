CC=$(prefix)g++
CPP_FLAGS:=-g -Wall -O3 -fPIC -ffast-math -finline-functions -std=c++11
CPP_FLAGS+=-Wno-format-zero-length -Wno-empty-body -Wno-comment -fpermissive
OBJ_DIR:=$(shell pwd)/obj

# 主目录需要的文件
CPP_FILE:=$(shell ls *.cpp)
OBJ:=$(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(basename $(notdir $(CPP_FILE)))))
DEPENDS:=$(addsuffix .d,$(OBJ))

INCLUDE:=-I.
LIB_SO:=-lncurses
# LIB_A:=

all:ssh_elf

-include $(DEPENDS)
$(OBJ):$(OBJ_DIR)/%.o:%.cpp
	$(CC) $(CPP_FLAGS) $(INCLUDE) -c $< -o $@
	$(CC) $(CPP_FLAGS) $(INCLUDE) -MM -MT $@ -MF $@.d $<

ssh_elf:$(OBJ)
	$(CC) $(CPP_FLAGS) $(OBJ_DIR)/*.o $(LIB_SO) -o $@

c:
	rm -f ./ssh_elf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.o.d ./.*.swp
