NAMESPACE = std

MACROS = NAMESPACE

NAME = map 

SRC = main.cpp 

OBJ = ${SRC:%.cpp=%.o}

FLAGS = -Wall -Werror -Wextra -fsanitize=address 

COMPILER = c++

STANDARD = -std=c++98


all: $(NAME)


$(NAME):

map_std:
	$(COMPILER) $(FLAGS) $(STANDARD) -D MAP=1 -D  NAMESPACE=std $(SRC) -o map_std

map_ft:
	$(COMPILER) $(FLAGS) $(STANDARD) -D MAP=1  -D NAMESPACE=ft $(SRC) -o map_ft

vector_std:
	$(COMPILER) $(FLAGS) $(STANDARD) -D VECTOR=1 -D  NAMESPACE=std $(SRC) -o vector_std

vector_ft:
	$(COMPILER) $(FLAGS) $(STANDARD) -D VECTOR=1  -D NAMESPACE=ft $(SRC) -o vector_ft

stack_std:
	$(COMPILER) $(FLAGS) $(STANDARD) -D STACK=1 -D  NAMESPACE=std $(SRC) -o stack_std

stack_ft:
	$(COMPILER) $(FLAGS) $(STANDARD) -D STACK=1 -D NAMESPACE=ft $(SRC) -o stack_ft


clean:
	rm -rf $(NAME) vector_ft vector_std map_ft map_std stack_std stack_ft

fclean: clean
	rm -rf $(NAME) vector_ft vector_std map_ft map_std stack_std stack_ft

re: fclean all

