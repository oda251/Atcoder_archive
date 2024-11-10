CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
################################################
################# Edit here ####################
################################################
# Edit to your own include path
INCLUDE = -I~/.ac-library
# Edit to your own output file name
NAME = out
################################################
################################################
SCRIPT_DIR = ./.scripts
GET_ACTIVE_FILE_SCRIPT = $(SCRIPT_DIR)/get_active_file_path.mjs
ACTIVE_FILE := $(shell $(GET_ACTIVE_FILE_SCRIPT))

all: $(ACTIVE_FILE)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(ACTIVE_FILE) -o $(NAME)