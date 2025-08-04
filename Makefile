# CXX = g++
# CXXFLAGS = -Wall -std=c++17 -Iinclude

# SRC = src/Song.cpp src/Playlist.cpp src/PlaybackStack.cpp main.cpp
# OBJ = $(SRC:.cpp=.o)
# TARGET = music_player

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# clean:
# 	rm -f $(OBJ) $(TARGET)

CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = music_player

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
