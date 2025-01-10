TARGET = mango
SRCDIR = src
BUILDDIR = buildTARGET = mango
SRCDIR = src
BUILDDIR = build
STBDIR = $(SRCDIR)/stb
CC = gcc
CFLAGS = -std=c2x -O3 -I$(STBDIR)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))
LIBS = -lm
STB_REPO = https://github.com/nothings/stb
JOBS = 4

all: $(STBDIR) $(BUILDDIR) $(TARGET)

$(STBDIR):
	git clone $(STB_REPO) $(STBDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

distclean: clean
	rm -rf $(STBDIR)

.PHONY: all clean distclean