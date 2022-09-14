PROJ=bridge_problem

# Compiler variables
CPP = g++
CPPFLAGS = -Wall
LIB_DIR = .
LIBS = -lyaml-cpp

# File variables
SRC_FILES = main.cpp

# Primary target
all: $(PROJ)

# Build executable
$(PROJ): $(SRC_FILES)
	$(CPP) $(CPPFLAGS) -o $@ $^ -L$(LIB_DIR) $(LIBS)

# Other Targets
clean:
	rm -rf $(PROJ)

.PHONY: all clean
