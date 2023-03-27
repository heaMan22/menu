SRC := menumain.c linklist.c
OBJ := $(SRC:%.c=%.o)

run : a.out
	./a.out

a.out : $(OBJ)
	gcc $^ -o a.out
