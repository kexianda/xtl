main.out : ./test/main.cpp xtl_construct.h xtl_type_trait.h xtl_memory.h xtl_iterator.h
	g++ -g -std=c++11 -o ./bin/Debug/main.out  ./test/main.cpp

clean :
	rm *.o
