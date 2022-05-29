CC = clang++
NAME = default_test
CT_PREF = containers
IT_PREF = iterators
CORE = core
SRC =		main.cpp \
			core/Assert.cpp
HEADERS =	$(CT_PREF)/map.hpp \
			$(CT_PREF)/pair.hpp \
			$(CT_PREF)/set.hpp \
			$(CT_PREF)/stack.hpp \
			$(CT_PREF)/vector.hpp
OBJ = $(SRC:.cpp=.o)
LDFLAGS =
FLAGS = -c -Wall -Wextra -Werror -std=c++98

all: $(SRC) $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@