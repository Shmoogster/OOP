SOURCES = $(wildcard source/*.cpp)
OBJECTS = $(patsubst source/%.cpp,source/%.o,$(SOURCES))
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I./include
LDFLAGS = -lm

all: game

game: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o game && rm -rf source/*.o

source/%.o : source/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf source/*.o game