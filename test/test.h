

#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include "../vector.h"
#include "../xtl_memory.h"

using namespace std;

struct Foo{
	Foo () {
	   val = 5;
   	   std::cout<<"Foo()" << std::endl;
	}

	int val;
	~Foo () {val = 0; std::cout<<"~Foo()"<<endl;}
};

namespace xtl_memeory_test {


	void test_xtl_Memory (){

		typedef xtl::allocator<Foo> FooAlloc;

		Foo* buff = FooAlloc::allocate (10);
		for (Foo* itr = buff; itr < buff+5; ++itr) {
			xtl::construct (itr);
		}

		Foo f;
		f.val = 888;
		for (Foo* itr = buff+5; itr < buff+10; ++itr) {
			xtl::copy_construct (itr, f);
		}

		xtl::destory(buff, buff+10); //[,)

		FooAlloc::deallocate (buff);
	}
}

namespace xtl_vector_test {
	struct Foo {
		Foo(int v) : val(v) {}
		int val;
	};
	void test() {

		typedef xtl::vector<Foo>	FooVector;


		// constructors used in the same order as described above:
		FooVector first;

		// four ints with value 100
		FooVector second (4, Foo(8));
		for (FooVector::iterator itr = second.begin(); itr < second.end(); ++itr ) {
            //test iterator, operator*,  operator->
			int tmp1 = (*itr).val;
			int tmp2 = itr->val;
			cout<<(tmp1 + tmp2)<<endl;
		}

		// iterating through second
		FooVector third (second.begin(), second.end());

		//copy constructor
		FooVector fourth (third);
		for (FooVector::iterator itr = fourth.begin(); itr < fourth.end(); ++itr ) {
            //test iterator, operator*,  operator->
			int tmp1 = (*itr).val;
			int tmp2 = itr->val;
			cout<< tmp1 + tmp2<<endl;
		}

		xtl::vector<int> invVect (5, 1) ; //1,1,1,1,1
		xtl::vector<int> invVect2(invVect); //


//		typedef	typename xtl::iterator_traits<int*>::value_type value_type1;
//        typedef	typename xtl::iterator_traits<int*>::value_type value_type2;
//        value_type1 i = 1;
//        value_type2 j = 2;
//
//
//        typedef typename xtl::_type_trait<value_type1>::is_pod_type type1;
//        typedef typename xtl::_type_trait<value_type2>::is_pod_type type2;
//        typedef	typename xtl::_bool_type_and<type1, type2>::type dispatch_type;
//        dispatch_type x ;

        //std::vector<Foo> stdFooVector (5, Foo(8)); // 8,8,8,8,8
        //std::vector<Foo> stdFooVector2 (stdFooVector);
        //std::vector<int> stdIntVector (5, 1);
        //std::vector<int> stdIntVector2(stdIntVector);
        //stdFooVector2.push_back(Foo(9));


		// the iterator constructor can also be used to construct from arrays:
        //Foo myFoos[] = {Foo(16), Foo(2),7 Foo(7), Foo(29)};
		//FooVector fifth (myints, myints + sizeof(myints) / sizeof(int) );
		//std::cout << "The contents of fifth are:";
 		//for (FooVector::iterator it = fifth.begin(); it != fifth.end(); ++it){

		//}

		//move constructor

		//initializer list constructor

	}
}

namespace xtl_iterator_test {

    //typedef xtl::iterator_traits
}


