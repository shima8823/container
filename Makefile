CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -pedantic-errors -MMD -MP
CPPFLAGS = -Iinclude/containers -Iinclude/utils
NAME_FT = ft_container
NAME_STL = stl_container

# ########### SRCS ########### #
SRCS = main.cpp test_vector.cpp utils.cpp
VPATH = test
# ############################ #

# ########### OBJS ########### #
OBJSDIR = $(OBJSDIR_FT) $(OBJSDIR_STL)

OBJSDIR_FT = obj_ft
OBJS_FT = $(addprefix $(OBJSDIR_FT)/, $(SRCS:%.cpp=%.o))

OBJSDIR_STL = obj_stl
OBJS_STL = $(addprefix $(OBJSDIR_STL)/, $(SRCS:%.cpp=%.o))

DEPENDS_FT = $(OBJS_FT:.o=.d)
DEPENDS_STL = $(OBJS_STL:.o=.d)
# ############################ #

all: $(OBJSDIR) $(NAME_FT) $(NAME_STL)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(NAME_FT): $(OBJS_FT)
	$(CXX) -o $(NAME_FT) $(OBJS_FT)

$(NAME_STL): $(OBJS_STL)
	$(CXX) -o $(NAME_STL) $(OBJS_STL)

$(OBJSDIR_FT)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(OBJSDIR_STL)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -D ISSTL=1 $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS_FT) $(DEPENDS_FT) $(OBJS_STL) $(DEPENDS_STL)

fclean: clean
	$(RM) $(NAME_FT) $(NAME_STL)

comp: $(NAME_FT) $(NAME_STL)
	./$(NAME_FT) > ft_result.txt
	./$(NAME_STL) > stl_result.txt
	diff ft_result.txt stl_result.txt

leaks: $(NAME_FT)
	leaks -q -atExit -- ./$(NAME_FT)

re: fclean all

-include $(DEPENDS_FT)
-include $(DEPENDS_STL)

.PHONY: all clean fclean re