
#ifndef _XTL_VECTOR_H
#define _XTL_VECTOR_H 1

#include "xtl_memory.h"
#include "xtl_allocate.h"
#include "xtl_iterator.h"

namespace xtl {

	template <typename T, typename Alloc = xtl::allocator<T> >
	class vector {
	public:
		typedef	T			value_type;
		typedef T&			reference;
		typedef const T&	const_reference;

		typedef T*			pointer;
		typedef const T*	const_pointer;

		typedef T*          iterator;

		typedef size_t		size_type;

		typedef Alloc		allocator_type;



		//todo:  reverse_iterator
		//reverse_iterator
		//const_reverse_iterator

		vector() : m_start(nullptr), m_finish(nullptr), m_end_of_storage(nullptr) {}


		explicit vector(size_type n, const value_type& val = value_type()) {
			this->m_start = allocator_type::allocate (n);
			this->m_finish = this->m_start + n;
			this->m_end_of_storage = this->m_start + n;

			//todo, to be improved
			for (size_type i=0; i < n; ++i) {
				xtl::copy_construct(m_start+i, val);
			}
		}


		vector (iterator from_itr, iterator to_itr) {
			typename iterator_traits<iterator>::difference_type n;

			n = distance (from_itr, to_itr);

			this->m_start = allocator_type::allocate (n);
			this->m_finish = this->m_start + n;
			this->m_end_of_storage = this->m_start + n;

			iterator curr = m_start;
			while (from_itr != to_itr) {
				copy_construct (curr++, *from_itr++);
			}
		}

		vector (const vector& v) {
			//todo
		}


#if __cplusplus >= 201103L
		//todo: move constructor. c++11
#endif //C++ 11


		~vector() {
			//todo
			xtl::destory(m_start, m_finish);
			allocator_type::deallocate(m_start);
		}



		iterator begin () {
			return this->m_start;
		}
		iterator end () {
		    //const_iterator
			return this->m_finish;
		}

	protected:
		iterator m_start;
		iterator m_finish;
		iterator m_end_of_storage;
	};
}


#endif /*_XTL_VECOTR_H*/
