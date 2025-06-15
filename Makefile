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

.PHONY: all clean fclean re bonus

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
	$(RM) $(OBJ_FILES) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

