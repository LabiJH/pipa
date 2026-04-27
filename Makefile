CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -fsanitize=address,undefined
PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
TARGET := peloader

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f peloader

install:
	install -d $(PREFIX)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)

.PHONY: clean install uninstall
