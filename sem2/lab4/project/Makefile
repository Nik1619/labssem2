TARGET=exe

HEADERS=./include/list_node.h
SOURCES=./src/main.c ./src/list_node.c
CFLAGS+=

.PHONY: all clean
all: $(TARGET) 
	

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -I ./include -ggdb ./src/*.c -o $(TARGET)


.PHONY: clean
clean:
	rm -f $(TARGET)
