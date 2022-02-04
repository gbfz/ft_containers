name		:=	ft_containers.out
includes	:=	utilities iterator vector stack rbtree map set

objs		:=	main.o
objdir		:=	./objs

cxx		:=	c++
cxxflags	:=	-Wall -Wextra -Werror -std=c++98
incflags	:=	$(addprefix -I, $(includes))
#dflags		:=	-g
oflags		:=	-O2

all:			create_objdir $(name)

create_objdir:
			@mkdir -p $(objdir)

deps		:=	$(patsubst %.o, %.d, $(objs))
-include		$(deps)
depflags	=	-MMD -MF $(@:.o=.d)

$(name):		$(objdir)/$(objs) Makefile
			$(cxx) $(cxxflags) $(oflags) $(dflags) $(incflags) $(objdir)/$(objs) -o $(name)

$(objdir)/%.o:		%.cpp Makefile
			$(cxx) $(cxxflags) $(oflags) $(dflags) $(incflags) $(depflags) -c $< -o $@

clean:
			rm -rf $(objdir)

fclean:			clean
			rm -f $(name)

re:			fclean all

run:			all
			clear
			./$(name)

.PHONY:			all clean fclean re run
