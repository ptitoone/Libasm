OS				:=	$(shell uname -s)

NAME			=	libasm.a
NAME_BONUS		=	libasm_bonus.a

BIN				=	libasm.out
BIN_BONUS		=	libasm_bonus.out

SRCS			:=	$(shell echo *.s)
SRCS_BONUS		:=	$(shell echo bonus/*.s)

OBJS			=	$(SRCS:.s=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.s=.o)

MAIN			=	main.c
MAINOBJ			=	main.o

MAIN_BONUS		=	bonus/main_bonus.c
MAINOBJ_BONUS	=	bonus/main_bonus.o

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -no-pie

AC				=	nasm
ACFLAGS			=	-f elf64 -g -F dwarf

.PHONY	:	all clean fclean re bonus

all : $(NAME) $(MAIN)

bonus : fclean $(NAME_BONUS) $(MAIN_BONUS)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(NAME_BONUS) : $(OBJS_BONUS) $(OBJS)
	ar rcs $(NAME_BONUS) $(OBJS_BONUS) $(OBJS)

.s.o :
	$(AC) $(ACFLAGS) $< -o $@

$(MAIN) : $(MAINOBJ)
	$(CC) -o $(BIN) $(MAINOBJ) -L . -lasm $(CFLAGS)

$(MAIN_BONUS) : $(MAINOBJ_BONUS)
	$(CC) -o $(BIN_BONUS) $(MAINOBJ_BONUS) -L . -lasm_bonus $(CFLAGS)
	
$(MAINOBJ) :
	$(CC) -c -g $(MAIN)

$(MAINOBJ_BONUS) :
	$(CC) -c -g -o $(MAINOBJ_BONUS) $(MAIN_BONUS) $(CFLAGS)

clean :
	rm -rf $(OBJS) $(OBJS_BONUS) $(MAINOBJ) $(MAINOBJ_BONUS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS) $(BIN) $(BIN_BONUS)

re : fclean all

