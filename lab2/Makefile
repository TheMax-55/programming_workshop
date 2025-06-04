clear:
	rm -rf *.o *.a *_test

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

linear_allocator.o: linear_allocator.h linear_allocator.c
		gcc -g -c linear_allocator.c -o linear_allocator.o

linear_allocator.a: linear_allocator.o
		ar rc linear_allocator.a linear_allocator.o

linear_allocator_test.o: linear_allocator_test.c
		gcc -g -c linear_allocator_test.c -o linear_allocator_test.o

linear_allocator_test: linear_allocator_test.o linear_allocator.a
		gcc -g -static -o linear_allocator_test linear_allocator_test.o linear_allocator.a

pool_allocator.o: pool_allocator.h pool_allocator.c
		gcc -g -c pool_allocator.c -o pool_allocator.o

pool_allocator.a: pool_allocator.o
		ar rc pool_allocator.a pool_allocator.o

pool_allocator_test.o: pool_allocator_test.c
		gcc -g -c pool_allocator_test.c -o pool_allocator_test.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
		gcc -g -static -o pool_allocator_test pool_allocator_test.o pool_allocator.a

array_list.o: array_list.h array_list.c
		gcc -g -c array_list.c -o array_list.o

array_list.a: array_list.o
		ar rc array_list.a array_list.o

array_list_test.o: array_list_test.c
		gcc -g -c array_list_test.c -o array_list_test.o

array_list_test: array_list_test.o array_list.a linear_allocator.a
		gcc -g -static -o array_list_test array_list_test.o array_list.a linear_allocator.a

hash_table.o: hash_table.h hash_table.c
		gcc -g -c hash_table.c -o hash_table.o

hash_table.a: hash_table.o
		ar rc hash_table.a hash_table.o

hash_table_test.o: hash_table_test.c
		gcc -g -c hash_table_test.c -o hash_table_test.o

hash_table_test: hash_table_test.o hash_table.a pool_allocator.a
		gcc -g -static -o hash_table_test hash_table_test.o hash_table.a pool_allocator.a

test: linear_allocator_test pool_allocator_test array_list_test hash_table_test
		./linear_allocator_test
		./pool_allocator_test
		./array_list_test
		./hash_table_test
