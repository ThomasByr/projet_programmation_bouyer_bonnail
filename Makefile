CC = gcc-11

CFLAGS ?= -march=znver3 -Ofast -pipe -std=c18 -pedantic -Wall -Wextra -Werror
LDLIBS ?= -lm # -pthread -ltps -lSDL2 -lSDL2_ttf

INCLUDE_PATH = ./includes

TARGET    = main

SRCDIR    = src
OBJDIR    = obj
BINDIR    = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all : $(BINDIR)/$(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: clean $(BINDIR)/$(TARGET)
	@echo "\033[33mRunning in debug mode!\033[0m"

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mLinking complete!\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
