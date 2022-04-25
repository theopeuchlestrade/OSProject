DEBUG=yes
PROG=exo1 exo2
CC=clang

ifeq ($(DEBUG),yes)
    CFLAGS=-g3 -Wall -pthread
    LDFLAGS=
else
    CFLAGS=-Wall -pthread
    LDFLAGS=
endif

COMPILE=$(CC) $(CFLAGS)
RM=rm
BUILD=build

EXO1_SRC=$(wildcard exo1/*.c)
EXO1_OBJ=$(EXO1_SRC:.c=.o)

EXO2_SRC=$(wildcard exo2/*.c)
EXO2_OBJ=$(EXO2_SRC:.c=.o)

EXO1_INCLUDES=$(wildcard exo1/*.h)
EXO2_INCLUDES=$(wildcard exo2/*.h)

all: $(PROG)
ifeq ($(DEBUG),yes)
	@echo "Building in debug mode"
else
	@echo "Building in release mode"
endif


# Exo 1 #

exo1: $(EXO1_OBJ)
ifeq ($(DEBUG),yes)
	@echo "\033[92m[info]\033[0m Linking :" $@ $^
else

endif
	@$(CC) -o ./build/bin$@ ./build/$^ $(LDFLAGS) # TODO change



exo1.o: $(EXO1_INCLUDES)

# Exo 2 #
exo2: $(EXO2_OBJ)
ifeq ($(DEBUG),yes)
	@echo "\033[92m[info]\033[0m Linking :" $@ $^
else

endif
	$(CC) -o ./build/bin$@ ./build/$^ $(LDFLAGS) # TODO change


exo2.o: $(EXO2_INCLUDES)

# Common #
%.o: %.c build
ifeq ($(DEBUG),yes)
	@echo "\033[92m[info]\033[0m Compiling :" $@ "->" $<
else

endif
	$(COMPILE) -o ./build/$@ -c $<


# Make the build directory if it doesn't exist
build:
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/exo1
	mkdir -p $(BUILD)/exo2

# Delete the build directory and program
clean:
	$(RM) -rf $(BUILD)

# These rules do not correspond to a specific file
.PHONY: build clean all