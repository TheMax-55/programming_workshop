clear:
	rm -rf *.o *.a *_test

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

#quad_equations

quad_equations.o: quad_equations.h quad_equations.c
		gcc -g -c quad_equations.c -o quad_equations.o

quad_equations.a: quad_equations.o
		ar rc quad_equations.a quad_equations.o

quad_equations_test.o: quad_equations_test.c
		gcc -g -c quad_equations_test.c -o quad_equations_test.o

quad_equations_test: quad_equations_test.o quad_equations.a
		gcc -g -static -o quad_equations_test quad_equations_test.o quad_equations.a -lm

#integral

integral.o: integral.h integral.c
		gcc -g -c integral.c -o integral.o

integral.a: integral.o
		ar rc integral.a integral.o

integral_test.o: integral_test.c
		gcc -g -c integral_test.c -o integral_test.o

integral_test: integral_test.o integral.a
		gcc -g -static -o integral_test integral_test.o integral.a

#list

list.o: list.h list.c
		gcc -g -c list.c -o list.o

list.a: list.o
		ar rc list.a list.o

list_test.o: list_test.c
		gcc -g -c list_test.c -o list_test.o

list_test: list_test.o list.a
		gcc -g -static -o list_test list_test.o list.a

#stack

stack.o: stack.h stack.c
		gcc -g -c stack.c -o stack.o

stack.a: stack.o
		ar rc stack.a stack.o

stack_test.o: stack_test.c
		gcc -g -c stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
		gcc -g -static -o stack_test stack_test.o stack.a

test: quad_equations_test integral_test list_test stack_test
		./quad_equations_test
		./integral_test
		./list_test
		./stack_test
