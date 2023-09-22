CC = gcc

OUT_DIR = ./out
SRC_DIR = ./src

INC_DIR = ./inc


CFLAGS = -std=gnu99

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.d)

INCLUDES = -I$(INC_DIR)

$(shell if [ ! -d "$(OUT_DIR)" ]; then mkdir $(OUT_DIR); fi)

all: chess.exe

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c -o $@ $<

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c 
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c -o $@ $<

chess.exe: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

-include $(OUT_DIR)/*.d

clang:
	clang-format -i src/*.c inc/*.h

clean:
	rm -rf $(OUT_DIR) chess.exe

.PHONY: clean
