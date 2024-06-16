NAME = out.exe
EXE = $(addprefix ./, $(NAME))
SRCS = $(wildcard ./in/*.txt)
RESS = $(patsubst ./in/%.txt, ./result/%.txt, $(SRCS))
RM = del

.PHONY: fclean clean test all culc avr

all: $(NAME)

$(NAME): main.cpp
	@g++ $< -o $@

culc: $(RESS)
	@python3 avr.py

./result/%.txt: ./in/%.txt $(NAME)
	@$(NAME) < $< > $@

clean:
	@$(RM) $(RESS)

fclean:
	@$(RM) $(NAME)

test:
	@g++ .\main.cpp && type .\0000.txt | .\a.exe > result0.txt && type .\0001.txt | .\a.exe > result1.txt && type .\0002.txt | .\a.exe > result2.txt && type .\0003.txt | .\a.exe > result3.txt && type .\0004.txt | .\a.exe > result4.txt

mini:
	@$(NAME) < in/0000.txt > 0000.txt
