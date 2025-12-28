CC = gcc
CFLAGS = -Os -Wall -Wextra -ffunction-sections -fdata-sections \
         -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-stack-protector
         

LDFLAGS = -Wl,--gc-sections -s

SRC_DIR = usr
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/breadbutter

CMDS = echo mkdir cat ls rm pwd chmod cz touch ln cp mv head \
       tail grep df true false id kill date du uname sleep \
       basename dirname env wc tee uniq whoami printf tr find \
       comm cut logname nohup sort xargs sed awk \
       alias unalias cal cd cksum diff getconf logger mesg pathchk time \
       expr test tty dd ps

OBJS = $(OBJ_DIR)/main.o $(patsubst %, $(OBJ_DIR)/%.o, $(CMDS))

all: $(TARGET) symlinks

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking BRB..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Final binary size: $$(du -h $(TARGET) | cut -f1)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

symlinks:
	@echo "Creating symlinks in $(BIN_DIR)..."
	@for cmd in $(CMDS); do \
		ln -sf breadbutter $(BIN_DIR)/$$cmd; \
	done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean symlinks
