NAME = libasm.a

NASM = nasm
NASMFLAGS = -f elf64

SRC_FILES := $(filter-out %_bonus.s, $(wildcard *.s))
OBJ_FILES := $(SRC_FILES:.s=.o)

BONUS_SRC := $(wildcard *_bonus.s)
BONUS_OBJ := $(BONUS_SRC:.s=.o)

AR = ar rc
RANLIB = ranlib
RM = rm -f

C_TEST = tests.c
TEST_BIN = test

.PHONY: all clean fclean re bonus test run

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES)
	$(RANLIB) $(NAME)

bonus: $(OBJ_FILES) $(BONUS_OBJ)
	$(AR) $(NAME) $(OBJ_FILES) $(BONUS_OBJ)
	$(RANLIB) $(NAME)

%.o: %.s
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	$(RM) $(OBJ_FILES) $(BONUS_OBJ) $(TEST_BIN) *.txt

fclean: clean
	$(RM) $(NAME)

test: libasm.a tests.c
	gcc -Wall -Wextra -Werror tests.c -L. -lasm -o test

run: test
	./$(TEST_BIN)

re: fclean all

