SOURCES = $(wildcard source/*.cpp)
OBJECTS = $(patsubst source/%.cpp,source/%.o,$(SOURCES))
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I./include -g
LDFLAGS = -lm

all: game

game: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o game

source/%.o : source/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf source/*.o game