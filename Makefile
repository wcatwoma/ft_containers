COLORGREEN = \033[32m
COLORREED = \033[31m
COLORWHITE = \033[0m

NAME_V = vector_test
NAME_L = list_test
NAME_M = map_test
NAME_Q = queue_test
NAME_S = stack_test

SRCS_V = ./vector/test.cpp
SRCS_L = ./list/test.cpp
SRCS_M = ./map/test.cpp
SRCS_Q = ./queue/test.cpp
SRCS_S = ./stack/test.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

OBJ_V = $(SRCS_V:.cpp=.o)
OBJ_L = $(SRCS_L:.cpp=.o)
OBJ_M = $(SRCS_M:.cpp=.o)
OBJ_Q = $(SRCS_Q:.cpp=.o)
OBJ_S = $(SRCS_S:.cpp=.o)

%.o: %.c
	@@clang++ -I  -c $< -o $@

all: $(NAME_V) $(NAME_L) $(NAME_M) $(NAME_Q) $(NAME_S)

vector: $(NAME_V)
	@./$(NAME_V)

list: $(NAME_L)
	@./$(NAME_L)

map: $(NAME_M)
	@./$(NAME_M)

queue: $(NAME_Q)
	@./$(NAME_Q)

stack: $(NAME_S)
	@./$(NAME_S)

check:
	@./$(NAME_V)
	@./$(NAME_L)
	@./$(NAME_M)
	@./$(NAME_Q)
	@./$(NAME_S)


$(NAME_V): $(OBJ_V)
	@clang++ $(FLAGS) $^ -o $@
	@echo "$(COLORGREEN)Assembled vector!$(COLORWHITE)"

$(NAME_L): $(OBJ_L)
	@clang++ $(FLAGS) $^ -o $@
	@echo "$(COLORGREEN)Assembled list!$(COLORWHITE)"

$(NAME_M): $(OBJ_M)
	@clang++ $(FLAGS) $^ -o $@
	@echo "$(COLORGREEN)Assembled map!$(COLORWHITE)"

$(NAME_Q): $(OBJ_Q)
	@clang++ $(FLAGS) $^ -o $@
	@echo "$(COLORGREEN)Assembled queue!$(COLORWHITE)"

$(NAME_S): $(OBJ_S)
	@clang++ $(FLAGS) $^ -o $@
	@echo "$(COLORGREEN)Assembled stack!$(COLORWHITE)"

clean:
	@rm -f ./*/*.o
	@echo "$(COLORREED)Deleted the object files.$(COLORWHITE)"

fclean: clean
	@rm -f $(NAME_V)
	@rm -f $(NAME_L)
	@rm -f $(NAME_M)
	@rm -f $(NAME_Q)
	@rm -f $(NAME_S)
	@echo "$(COLORREED)Deleted all containers.$(COLORWHITE)"

re: fclean all

.PHONY: all start clean fclean re vector list map queue stack check