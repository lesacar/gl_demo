CC = x86_64-w64-mingw32-g++
CLFAGS = -Wall -Wextra
LIB = -Ldeps/glfw3/lib -Ldeps/glut/lib/x64
LIBS = -lglfw3 -lopengl32 -lgdi32 -static
INCLUDE = -Ideps/ -Ideps/glfw3/include

BUILD_DIR = build
TARGET = $(BUILD_DIR)/game.exe
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = dbg
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE) $(LIB) $(CFLAGS) $^ -o $@ $(LIBS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(LIB) $(CFLAGS) -c $< -o $@ $(LIBS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) -rf $(BUILD_DIR) $(OBJ_DIR)
