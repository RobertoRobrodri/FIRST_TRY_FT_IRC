# COLORS #
#
GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m" 
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
RESET 	= "\033[1;0m"

# VARIABLES #
#
NAME 		= ircserv
CC 			= c++
INCLUDE 	= -std=c++98
CXXFLAGS 	= -Wall -Wextra -Werror

# PATHs #
#
SRC_PATH    	= srcs
SUBFILE1_PATH   = server
SUBFILE2_PATH   = client
SUBFILE3_PATH   = msg
OBJ_PATH    	= objects
TEST_PATH		= test

# SOURCES #

SUBFILE1_SRC = server.cpp

SUBFILE2_SRC = client.cpp

SUBFILE3_SRC = msg.cpp

SRC =  	main.cpp \
		$(addprefix $(SUBFILE1_PATH)/, $(SUBFILE1_SRC)) \
		$(addprefix $(SUBFILE2_PATH)/, $(SUBFILE2_SRC)) \
		$(addprefix $(SUBFILE3_PATH)/, $(SUBFILE3_SRC)) 



# RULES #
all: $(NAME)

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(SRC:%.cpp=%.o))



$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE1_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE2_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE3_PATH))


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
            
$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
#clear
	$(GREEN) Program asembled $(RESET)

##RULES
$(MAKE): make

clean:
	$(PURPLE) CLEANING OBJECTS $(RESET)
	rm -rf $(OBJ_PATH)
	
fclean: clean tclean
	$(PURPLE) CLEANING DIRECTORY AND EXEC $(RESET)
	rm -rf $(NAME)
	rm -rf $(OBJ_PATH)

re: fclean all

test:
	@echo "##################################################################################"
	@echo "#                         Generating test folder                                 #"
	@echo "##################################################################################"
	@mkdir -p $(TEST_PATH)
	@for FILE in $(SRC_PATH)/* ; do ln -sf $(PWD)/$(SRC_PATH)/* $(PWD)/$(TEST_PATH)/$(basename($$FILE)) ; done;
	@if [ ! -f "$(TEST_PATH)/main.cpp" ]; then \
		echo "int main(int argc, char **argv)" >> $(PWD)/$(TEST_PATH)/main.cpp \
		echo "{" >> $(PWD)/$(TEST_PATH)/main.cpp \
		echo "return (0);" >> $(PWD)/$(TEST_PATH)/main.cpp \
		echo "}" >> $(PWD)/$(TEST_PATH)/main.cpp ;\
	fi
	@echo "⠀⠀⠀	    ⣠⣴⣶⣿⣿⣷⣶⣄⣀⣀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣾⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⡟⠁⣰⣿⣿⣿⡿⠿⠻⠿⣿⣿⣿⣿⣧⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⠏⠀⣴⣿⣿⣿⠉⠀⠀⠀⠀⠀⠈⢻⣿⣿⣇⠀⠀⠀\n\
⠀⠀⠀⠀⢀⣠⣼⣿⣿⡏⠀⢠⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⡀⠀⠀\n\
⠀⠀⠀⣰⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡇⠀⠀\n\
⠀⠀⢰⣿⣿⡿⣿⣿⣿⡇⠀⠘⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⢀⣸⣿⣿⣿⠁⠀⠀\n\
⠀⠀⣿⣿⣿⠁⣿⣿⣿⡇⠀⠀⠻⣿⣿⣿⣷⣶⣶⣶⣶⣶⣿⣿⣿⣿⠃⠀⠀⠀\n\
⠀⢰⣿⣿⡇⠀⣿⣿⣿⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀\n\
⠀⢸⣿⣿⡇⠀⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠛⠉⢉⣿⣿⠀⠀⠀⠀⠀⠀\n\
⠀⢸⣿⣿⣇⠀⣿⣿⣿⠀⠀⠀⠀⠀⢀⣤⣤⣤⡀⠀⠀⢸⣿⣿⣿⣷⣦⠀⠀⠀\n\
⠀⠀⢻⣿⣿⣶⣿⣿⣿⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣦⡀⠀⠉⠉⠻⣿⣿⡇⠀⠀\n\
⠀⠀⠀⠛⠿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠈⠹⣿⣿⣇⣀⠀⣠⣾⣿⣿⡇⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣦⣤⣤⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢿⣿⣿⣿⣿⣿⣿⠿⠋⠉⠛⠋⠉⠉⠁⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠁\n"
	@echo "##################################################################################"
	@echo "#               Test ready pls edit main.cpp with you own test                   #"
	@echo "##################################################################################"

tclean:
	rm -rf $(TEST_PATH)

PHONY.: all clean fclean re
