NAME = ft_container
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address
CC = clang++

CFLAGS += -I ./Iterators/ -I./vector/ -I ./utils/

FILES = vector.cpp

SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(FILES))) 

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : 
	$(CC) $(CFLAGS) -g -o $(NAME) main.cpp 

%.o : %.cpp
	$(CC) $(CFLAGS) -g -c -o $@ $^

clean :
	rm -f $(OBJS) $(C_OBJS)

fclean :
	rm -f $(OBJS) $(C_OBJS) $(NAME)

re : fclean all

.PHONY: clean fclean all re bonus
