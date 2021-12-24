CC = gcc-11
TARGET = tests

CFLAGS = -march=znver3 -O3 -pipe -std=c18 -pedantic -fprofile-arcs -ftest-coverage -Wall -Wextra -Werror # -g
LDLIBS = -lm # -pthread -ltps -lSDL2 -lSDL2_ttf

INCLUDE_PATH = ../includes

SRCDIR   = ../src
OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS0  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS = $(filter-out $(OBJDIR)/main.o,$(OBJECTS0))

tests: $(OBJECTS) obj/tests.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

cov: clean tests
	valgrind --leak-check=full -q ./$(TARGET)
	lcov -d obj -c -o report.info
	genhtml -o report -t "Coverage" report.info

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)

obj/tests.o: tests.c
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
