PROJ=bridge_problem

# Compiler variables
CPP = g++
CPPFLAGS = -Wall
LIBS = -L. -lc -lm -lyaml-cpp

# File variables
SRC_FILES = main.cpp

# Primary target
all: $(PROJ)

# Build executable
$(PROJ): $(SRC_FILES)
	$(CPP) $(CPPFLAGS) -o $@ $^  $(LIBS)

# Other Targets
clean:
	rm -rf $(PROJ)

.PHONY: all clean
