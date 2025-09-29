NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

SRC = 	main.cpp \
		BitcoinExchange.cpp \

OBJ = 		$(SRC:.cpp=.o)

all: 		$(NAME)

$(NAME): 	$(OBJ)
			$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: fclean all 