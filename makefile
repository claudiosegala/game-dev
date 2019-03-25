# CC=g++
# EXECNAME = game.out
# SRCDIR = src
# INCDIR = include
# BINDIR = bin
# OBJDIR = object
# RESDIR = resources
# LFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
# CFLAGS = -Wall -Wextra -pedantic -std=c++11 -O3 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector

# BIN = $(BINDIR)/$(EXECNAME)
# SRC = $(wildcard $(SRCDIR)/*.cpp)
# OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# all: $(OBJ)
# 	$(CC) $(OBJ) $(LFLAGS)  $(CFLAGS) -o $(EXECNAME) -g -ggdb

# %.o: $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@)
# 	$(CC) -c $(CFLAGS) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) -o $@ -g -ggdb

# run: all
# 	./game.out

# clean:
# 	rm -f $(OBJ) *~

# config:
# 	brew install sdl2
# 	brew install sdl2_image
# 	brew install sdl2_mixer
# 	brew install sdl2_ttf


CC = g++
RMDIR = rm -rf
RM = rm -f

RUN = ./

DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d

DIRECTIVES = -std=c++11 -Wall -Wextra -pedantic -std=c++11 -O3 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wshift-overflow  -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -c -I $(HEADER_PATH)

LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = game.out

ifeq ($(OS),Windows_NT)

RMDIR = rd /s /q
RM = del

RUN =

SDL_PATH = C:\SDL2\SDL2-2.0.5\x86_64-w64-mingw32

DIRECTIVES += -I $(SDL_PATH)\include\SDL2

LIBS = -L $(SDL_PATH)\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

# ifeq ($(UNAME_S), Darwin)
# LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
# endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)  -fsanitize=address

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp

ifeq ($(OS), Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)

print-% : ; @echo $* = $($*)

debug: DIRECTIVES += -ggdb -O0 -DDEBUG
debug: all

dev: debug run

gdb: RUN := gdb $(RUN)
gdb: dev

release: DIRECTIVES += -Ofast -mtune=native
release: all

run:
	$(RUN)$(EXEC)

clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(EXEC)

.PRECIOUS: $(DEP_PATH)/%.D

.PHONY: debug clean release

-include $(DEP_FILES)