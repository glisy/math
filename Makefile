## Project settings
PROJECT_NAME ?= GlisyMath
PREFIX ?= /usr/local

## Project command dependencies
MKDIR ?= mkdir -p
RM ?= rm -f
CP ?= cp -f

## Source files
SRC += $(wildcard src/*.c)

## Source objects
OBJS := $(SRC:.c=.o)

## Compiler flags
CFLAGS += -Ideps
CFLAGS += -Iinclude
CFLAGS += -Wall
CFLAGS += -O2

## Target static library
TARGET_STATIC := lib$(PROJECT_NAME).a

export TARGET_STATIC
export CFLAGS

## Builds everything
.PHONY: all
all: $(TARGET_STATIC)

## Builds static library
$(TARGET_STATIC): $(OBJS)
	if test $^; then $(AR) crus $@ $^; fi

## Compiles object files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

## Cleans project directory
.PHONY: clean
clean: test/clean
clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET_STATIC)

## Compiles and runs all test
.PHONY: test
test:
	if test -d; then $(MAKE) -C $@; fi

## Installs library into system
.PHONY: install
install: $(TARGET_STATIC)
	$(CP) -r include/* $(PREFIX)/include/
	$(CP)  $(TARGET_STATIC) $(PREFIX)/lib

## Uninstalls library from system
.PHONY: uninstall
uninstall:
	$(RM) -r $(PREFIX)/include/$(PROJECT_NAME)
	$(RM) $(PREFIX)/lib/$(TARGET_STATIC)

## Cleans test directory
.PHONY: test/clean
test/clean:
	if test -d test; then $(MAKE) clean -C test; fi
