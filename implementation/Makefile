EXTENSION = cpp
COMPILER  = g++
PACKAGES  =
EXTRAINCL =
EXTRALIBS =

MAINS   = search.cpp cluster.cpp main_test.cpp
CFLAGS  = -W -Wall -pedantic -O2 $(ALL_HDRS) -g -O0
LDFLAGS = $(ALL_LIBS)

#####
ALL_HDRS = $(foreach pack, $(PACKAGES), $(shell echo `pkg-config --cflags $(pack)`)) $(EXTRAINCL)
ALL_LIBS = $(foreach pack, $(PACKAGES), `pkg-config --libs $(pack)`) $(EXTRALIBS)

EXT     = $(EXTENSION)
CC      = $(COMPILER)
ALLSRC  = $(wildcard *.$(EXT))
SRC     = $(filter-out $(MAINS),$(ALLSRC))
OBJ     = $(SRC:.$(EXT)=.o)

.SECONDEXPANSION:
.PHONY: all clean mrproper list pkgs-avail pkgs-version help

#####
all: pkgs-avail $(MAINS:.$(EXT)=)

$(MAINS:.$(EXT)=): $(OBJ) $$(@).o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.$(EXT)
	$(CC) -o $@ -c $< $(CFLAGS)

#####
clean:
	rm -rf $(OBJ) $(MAINS:.$(EXT)=.o)

mrproper: clean
	rm -rf $(MAINS:.$(EXT)=)

list:
	@echo -e "Sources $(SRC)\nObjets  $(OBJ)\nMains   $(MAINS)"

pkgs-version:
	@for p in $(PACKAGES); do \
		echo -n "$$p : "; \
		pkg-config --modversion $$p; \
	done

pkgs-avail:
	@for p in $(PACKAGES); do \
		pkg-config --exists $$p; \
		if [ $$? -ne 0 ]; then \
			echo -en "\033[31m" > /dev/stderr; \
			echo -en "The package $$p does not exist" > /dev/stderr; \
			echo -e  "\033[0m" > /dev/stderr; \
		fi; \
	done