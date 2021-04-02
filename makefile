# Available commands:
# make - make the project
# make all - same
# make run - makes and then runs the program
# make clean - cleans output files

# Vars:
SOURCE	= src/main.cpp src/quickcg/quickcg.cpp
OUT		= out/test.out
CC		= g++
FLAGS	= -g -c -Wall
LFLAGS	= -lSDL -O3

# Terms used
.PHONY: all run clean

# Make the project: compiles
all: $(SOURCE) | out # checks if folder 'out' exists
	@echo "compiling..."
	@$(CC) $(SOURCE) -o $(OUT) $(LFLAGS)

# Run the project: compiles then runs
run: all
	@echo "running..."
	@./$(OUT)

# Create dir 'out' if it doesnt exist
out:
	mkdir -p $@

# Delete output files
clean:
	rm -f $(OUT)
