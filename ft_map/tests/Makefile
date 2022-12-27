NAMESPACE = std

MACROS = NAMESPACE

NAME = map 

SRC = main.cpp 

OBJ = ${SRC:%.cpp=%.o}

#FLAGS = -Wall -Werror -Wextra -fsanitize=address 
FLAGS = -Wall -Werror -Wextra 

COMPILER = c++

STANDARD = -std=c++98


all: $(NAME)

%.o:%.cpp
	$(COMPILER) -c $(FLAGS) $(STANDARD)  -D $(MACROS)=$(NAMESPACE) $< -o $@


$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(STANDARD) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) a.out

re: fclean all

t: test/tets.cpp
	c++  -Wall -Werror -Wextra -fsanitize=address $< -std=c++98

