CC = g++

FLAGS = -std=c++11 -Wall

FILES := main.cpp simpleshader.cpp

OBJDIR = obj
SRCDIR = src
BINDIR = bin

BIN = opengl

INCLUDE = -I include/ -lGLEW -lglfw -lGL

SOURCES := $(addprefix $(SRCDIR)/, $(FILES))
OBJECTS := $(addprefix $(OBJDIR)/, $(FILES:.cpp=.o))
BINARY = $(addprefix $(BINDIR)/, $(BIN))

.PHONY: clean

all: $(SOURCES) $(BINARY)


$(BINARY): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $(BINARY) $(INCLUDE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm $(OBJECTS) $(LIBARY)