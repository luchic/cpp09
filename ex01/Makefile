NAME = RPN

SRC_FOLDER = src
OBJ_FOLDER = out
INCLUDES = includes

SRC_FILES = RPN.cpp \
			main.cpp

OBJ_FILES = $(addprefix $(OBJ_FOLDER)/, $(SRC_FILES:.cpp=.o))

CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++17

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re