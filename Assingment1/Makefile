CC = gcc
CFLAGS = -Wall -g -I./includes
TARGET = main

all: $(TARGET)

$(TARGET): $(wildcard src/*.c)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

valin: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(TARGET) < tests/2.in

valout: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(TARGET) > test.out

# Pode trocar os números para diferentes testes
test: $(TARGET)
	for number in `seq 3 3`; do \
	./$(TARGET) < tests/$$number.in > tests/$$number.out2; \
	diff -s tests/$$number.out tests/$$number.out2; \
	done

hex:
	hexdump -Cv tec.bin

dif:
	diff tests/3.out tests/3.out2
