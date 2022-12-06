NAME = RubikCage
SRCS = RubikCage.cpp
CC = g++

prog : RubikCage.cpp
		$(CC) $(SRCS) -o $(NAME)