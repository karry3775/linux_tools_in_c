all: build myls

build:
	mkdir -p build

myls: ls.c
	gcc ls.c -o build/myls

format:
	clang-format -i *.c

clean: 
	rm -rf build

