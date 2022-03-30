TARGET = calc

CLIBS = -lm
CC = gcc

$(TARGET): main.o $(TARGET).o tree.o
	$(CC) $^ $(CLIBS) -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@

tree.o: Tree/tree.c Tree/tree.h
	$(CC) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

run:
	./$(TARGET)