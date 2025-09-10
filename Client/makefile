# 定义编译器
CC = gcc

# 定义编译选项
# -g: 生成调试信息
# -Wall: 开启所有警告
CFLAGS = -g -Wall

# 定义所有源文件
SRCS = core.c ui.c main.c

# 定义所有目标文件（.o 文件）
OBJS = $(SRCS:.c=.o)

# 定义最终的可执行文件名称
TARGET = client_app

# 定义 ncurses 库的链接选项
# -lncurses: 链接 ncurses 库
# LIBS = -lncurses

# 默认目标：编译和链接所有文件以生成可执行文件
all: $(TARGET)

# 编译生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# 编译 .c 源文件为 .o 目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理所有编译生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean