/*
 *	@Author: Ke, Xianda
 *	@Date: 2014-08-31
 *
 *	HP-Stlye allocators. a simple allocator
 *	no pool for small objects,  because  ms-crt / glibc will do the work. 
 *
 *
 * */
#ifndef _XTL_ALLOCATOR_H
#define _XTL_ALLOCATOR_H	1

#include <cstdlib> //malloc, free
#include <cstddef> //ptrdiff_t, size_t

namespace xtl {
	
	//exception
	//stuct bad_alloc {};

	template <typename T>
	inline T* _allocate (ptrdiff_t size, T* ) {
		T* tmp = (T*) malloc ( (size_t)(size * sizeof(T)) );
		if (nullptr == tmp) {
			std::bad_alloc ba; //use std::bad_alloc 
			throw ba;
		}
		return tmp;
	}

	template <typename T>
	inline void _deallocate (T* buf) {
		free (buf);
	}



	template<typename T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef const T&	reference;
		typedef T&			const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		static pointer allocate (size_t n) {
			return _allocate (n, (pointer)(0));
		}

		static void deallocate (pointer p) {
			_deallocate (p);
		}

		static pointer address (reference r) {
			return (pointer)&r;
		}

		static const_pointer const_address (reference r) {
			return (const_pointer)&r;
		}

		static size_type init_page_size () {
			size_type a = size_type(1);
			size_type b = size_type(4096/sizeof(value_type)) ;
			return a > b ? a : b;
		}
	};

}//end of xtl

#endif  /* _XTL_ALLOCATOR_H */
