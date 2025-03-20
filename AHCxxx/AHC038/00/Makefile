SHELL := /bin/bash
UNAME_S := $(shell uname -s)
CODE = ./.code.cpp
SRC = ./main.cpp \
	./lib.hpp \
	./type.hpp
EXE = ./a.out
T ?= 0000
TESTFILE = ../in/$(T).txt

ifeq ($(UNAME_S),Linux)
	CPPVERSION = -std=c++17
	PBCOPY = xclip -selection clipboard
else
	CPPVERSION = -std=c++17
	PBCOPY = pbcopy
endif

all: code
	@g++ $(SRC) -o $(EXE) $(CPPVERSION) -g -fsanitize=address

code:
	@cat ./lib.hpp > $(CODE)
	@tail -n +2 ./type.hpp >> $(CODE)
	@tail -n +2 ./main.cpp >> $(CODE)

test: all
	@echo "testing `printf "%04d" $(T)`.txt"
	@$(EXE) < ../in/`printf "%04d" $(T)`.txt | tee ./out.txt | $(PBCOPY)

testeasy: all
	@echo "testing 0.txt"
	@$(EXE) < ../in/0.txt | $(PBCOPY)

testhard: all
	@echo "testing -.txt"
	@$(EXE) < ../in/-.txt | $(PBCOPY)

test100: all
	@echo "Testing 100"
	@for i in {0..99}; do \
		echo "-- Testing $$i --"; \
		$(EXE) < ../in/`printf "%04d" $$i`.txt | $(PBCOPY); \
	done

run:
	@$(EXE) | $(PBCOPY)

fclean:
	rm -f $(EXE) $(CODE)

.PHONY: all code fclean
