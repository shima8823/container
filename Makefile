CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -pedantic-errors -MMD -MP -g
CPPFLAGS = -Iinclude/containers -Iinclude/utils
NAME_FT = ft_container
NAME_STL = stl_container
MY_TEST_NAME_FT = ft_output
MY_TEST_NAME_STL = stl_output

# ########### SRCS ########### #
SRCS = subject_test.cpp
MY_TEST_SRCS = main.cpp test_vector.cpp test_map.cpp test_stack.cpp utils.cpp
VPATH = test
# ############################ #

# ########### OBJS ########### #
OBJSDIR = $(OBJSDIR_FT) $(OBJSDIR_STL)

OBJSDIR_FT = obj_ft
OBJS_FT = $(addprefix $(OBJSDIR_FT)/, $(SRCS:%.cpp=%.o))
MY_TEST_OBJS_FT = $(addprefix $(OBJSDIR_FT)/, $(MY_TEST_SRCS:%.cpp=%.o))

OBJSDIR_STL = obj_stl
OBJS_STL = $(addprefix $(OBJSDIR_STL)/, $(SRCS:%.cpp=%.o))
MY_TEST_OBJS_STL = $(addprefix $(OBJSDIR_STL)/, $(MY_TEST_SRCS:%.cpp=%.o))

DEPENDS_FT = $(OBJS_FT:.o=.d)
MY_TEST_DEPENDS_FT = $(MY_TEST_OBJS_FT:.o=.d)
DEPENDS_STL = $(OBJS_STL:.o=.d)
MY_TEST_DEPENDS_STL = $(MY_TEST_OBJS_STL:.o=.d)
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
	$(RM) $(MY_TEST_OBJS_FT) $(MY_TEST_DEPENDS_FT) $(MY_TEST_OBJS_STL) $(MY_TEST_DEPENDS_STL)

fclean: clean
	$(RM) $(NAME_FT) $(NAME_STL)
	$(RM) $(MY_TEST_NAME_FT) $(MY_TEST_NAME_STL)

# example make bench seed=42
bench: $(NAME_FT) $(NAME_STL)
	time ./$(NAME_FT) $(seed)
	time ./$(NAME_STL) $(seed)

# ########### MY TEST ########### #
mytest: $(OBJSDIR) $(MY_TEST_NAME_FT) $(MY_TEST_NAME_STL)

$(MY_TEST_NAME_FT): $(MY_TEST_OBJS_FT)
	$(CXX) -o $(MY_TEST_NAME_FT) $(MY_TEST_OBJS_FT)

$(MY_TEST_NAME_STL): $(MY_TEST_OBJS_STL)
	$(CXX) -o $(MY_TEST_NAME_STL) $(MY_TEST_OBJS_STL)

comp: mytest
	./$(MY_TEST_NAME_FT) > ft_result.txt
	./$(MY_TEST_NAME_STL) > stl_result.txt
	diff ft_result.txt stl_result.txt

leaks: $(MY_TEST_NAME_FT)
	leaks -q -atExit -- ./$(MY_TEST_NAME_FT)
# ############################### #

re: fclean all

-include $(DEPENDS_FT)
-include $(DEPENDS_STL)
-include $(MY_TEST_DEPENDS_FT)
-include $(MY_TEST_DEPENDS_STL)

.PHONY: all clean fclean re leaks comp mytest bench