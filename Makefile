CXX = c++
CXXFLAGS = -std=c++98
# CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -pedantic-errors -MMD -MP
CPPFLAGS = -Iinclude/containers -Iinclude/utils
NAME = container

SRCS = main.cpp test_vector.cpp utils.cpp
VPATH = test

OBJSDIR = obj
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:%.cpp=%.o))
DEPENDS = $(OBJS:.o=.d)

all: $(OBJSDIR) $(NAME)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

$(OBJSDIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(DEPENDS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re