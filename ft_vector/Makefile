NAME = ft_vector 

SRC = main1.cpp 

OBJ = ${SRC:%.cpp=%.o}

FLAGS = -Wall -Werror -Wextra -fsanitize=address 

COMPILER = c++

STANDARD = -std=c++98

all: $(NAME)

%.o:%.cpp
	$(COMPILER) -c $(FLAGS) $(STANDARD) $< -o $@


$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(STANDARD) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) a.out

re: fclean all

test : test.cpp
	c++  -Wall -Werror -Wextra -fsanitize=address test.cpp -std=c++98

