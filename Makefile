name		:=	vectest
includes	:=	utilities iterator vector

objs		:=	main.o
objdir		:=	./objs
#objs		:=	$(addprefix $(objdir)/, $(objs))

cxx		:=	clang++
cxxflags	:=	-Wall -Wextra -Werror -std=c++98
incflags	:=	-I $(includes)
dflag		:=	-g
oflag		:=	#-O2

all:			create_objdir $(name)

create_objdir:
			@mkdir -p $(objdir)

deps		:=	$(patsubst %.o, %.d, $(objs))
-include		$(deps)
depflags	=	-MMD -MF $(@:.o=.d)

$(name):		$(objdir)/$(objs) Makefile
			$(cxx) $(cxxflags) $(oflag) $(dflag) -I utilities -I iterator -I vector $(objdir)/$(objs) -o $(name)

$(objdir)/%.o:		%.cpp Makefile
			$(cxx) $(cxxflags) $(oflag) $(dflag) -I utilities -I iterator -I vector $(depflags) -c $< -o $@

clean:
			rm -rf $(objdir)

fclean:			clean
			rm -f $(name)

re:			fclean all

run:			all
			clear
			./$(name)

.PHONY:			all clean fclean re run
