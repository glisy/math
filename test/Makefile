SRC := $(wildcard *.c)
TESTS := $(SRC:.c=)
CFLAGS += -I../include

all: $(TESTS)
$(TESTS): $(SRC)
	$(CC) $(CFLAGS) $@.c -o $@
	./$@

clean:
	$(RM) $(SRC:.c=)
