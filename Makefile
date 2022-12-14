source = src
include = include
build ?= build
flags ?= -O -Wall -Werror
cc ?= arm-linux-gnueabi-gcc

sources ?= $(wildcard $(source)/*.c)
objects = $(patsubst $(source)/%.c, $(build)/%.o, $(sources))

.PHONY: clean clear

all: $(build)/libev3min.so

$(build)/%.o: $(source)/%.c
	$(cc) -I$(include) $(flags) -c -fpic $< -o $@

$(build)/libev3min.so: $(objects)
	$(cc) -shared -o $(build)/libev3min.so $^

clean:
	rm -f $(build)/*.o

clear:
	rm $(build)/*
