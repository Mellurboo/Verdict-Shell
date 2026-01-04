#
# Target Output Details
#
ELF_TARGET_64 = verdict
#
# Flag Options for Compilers
#
CFLAGS ?=
COMMON_CFLAGS = -static -Wall -nostdlib -ffreestanding -fno-stack-check -fno-stack-protector -Wextra -Werror -I include

ELF_BIN_DIR_64 = bin
ELF_OBJ_DIR_64 = $(ELF_BIN_DIR_64)/obj

#
# Detect Source files in Code, this is very broad
# and will just compile anything it finds
#
SRCS = $(shell find src -name '*.c')

ELF_OBJS_64 = $(patsubst src/%.c, $(ELF_OBJ_DIR_64)/%.gcc.o, $(SRCS))

all: $(ELF_TARGET_64)

#
# Build ELF
#
$(ELF_TARGET_64): $(ELF_OBJS_64)
	@mkdir -p $(ELF_BIN_DIR_64)
	$(CC) $(COMMON_CFLAGS) $(CFLAGS) -m64 -o $(ELF_BIN_DIR_64)/$(ELF_TARGET_64) $^

#
# Object build rules per architecture
#
$(ELF_OBJ_DIR_64)/%.gcc.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(COMMON_CFLAGS) $(CFLAGS) -m64 -c $< -o $@


build: $(ELF_TARGET_64)
	@./$(ELF_BIN_DIR_64)/$(ELF_TARGET_64)

#
# Clean
#
clean:
	rm -rf bin
	rm -rf .vscode

.PHONY: all clean -fno-stack-check debug