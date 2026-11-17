CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
INCLUDES = -Isrc

BUILD_DIR = build
TARGET = student_records.exe

SOURCES = src/main.c src/student.c src/file_manager.c
OBJECTS = $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
