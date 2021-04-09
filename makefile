# Available commands:
# make - make the project
# make all - same
# make run - makes and then runs the program
# make clean - cleans output files
# make run-raycaster-flat - makes and runs flat raycaster example
# make run-raycaster-textured - makes and runs textured raycaster example

# Vars:
SOURCE	= src/main.cpp src/quickcg/quickcg.cpp src/functions.h
OUT		= out/test.out
CC		= g++
FLAGS	= -g -c -Wall
LFLAGS	= -lSDL_image -lSDL -O3

# Terms used
.PHONY: main run raycaster-flat raycaster-textured run-raycaster-flat run-raycaster-textured clean

# Make the project: compiles
main: $(SOURCE) | out # checks if folder 'out' exists
	@echo "compiling main.cpp..."
	@$(CC) $(SOURCE) -o $(OUT) $(LFLAGS)

raycaster-flat: src/raycaster_flat.cpp src/quickcg/quickcg.cpp | out
	@echo "compiling raycaster_flat.cpp..."
	@$(CC) src/raycaster_flat.cpp src/quickcg/quickcg.cpp -o out/raycaster_flat.out $(LFLAGS)

raycaster-textured: src/raycaster_textured.cpp src/quickcg/quickcg.cpp | out
	@echo "compiling raycaster_textured.cpp..."
	@$(CC) src/raycaster_textured.cpp src/quickcg/quickcg.cpp -o out/raycaster_textured.out $(LFLAGS)

# Run the project: compiles then runs
run: main
	@echo "running main.cpp..."
	@./$(OUT)

run-raycaster-flat: raycaster-flat
	@echo "running raycaster-flat.cpp..."
	@./out/raycaster_flat.out

run-raycaster-textured: raycaster-textured
	@echo "running raycaster-textured.cpp..."
	@./out/raycaster_textured.out

# Create dir 'out' if it doesnt exist
out:
	mkdir -p $@

# Delete output files
clean:
	rm -f $(OUT) out/raycaster_flat.out out/raycaster_textured.out
