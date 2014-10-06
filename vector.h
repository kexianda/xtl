/**
 *  Copyleft (c) 2014
 *	@Author: Ke, Xianda
 *	@Date: 2014-08-31
 *
 *	implement a stl::vector like container: xtl:vetcor
 *
 *
 *
 * */

/**
 *   Copyright (c) 1994
 *   Hewlett-Packard Company
 *
 *   Permission to use, copy, modify, distribute and sell this software
 *   and its documentation for any purpose is hereby granted without fee,
 *   provided that the above copyright notice appear in all copies and
 *   that both that copyright notice and this permission notice appear
 *   in supporting documentation.  Hewlett-Packard Company makes no
 *   representations about the suitability of this software for any
 *   purpose.  It is provided "as is" without express or implied warranty.
 *
 **/


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

		vector() : m_start(nullptr), m_finish(nullptr), m_end_of_storage(nullptr), m_size(0) {}


		explicit vector(size_type n, const value_type& val = value_type()) {
			this->m_start = allocator_type::allocate (n);
			this->m_finish = this->m_start + n;
			this->m_end_of_storage = this->m_start + n;
			this->m_size = n;

			xtl::uninitialized_fill_n(this->m_start, n, val);

			//todo, to be improved for POD type
			//for (size_type i=0; i < n; ++i) {
			//	xtl::copy_construct(m_start+i, val);
			//}
		}


		vector (iterator from_itr, iterator to_itr) {
			typename iterator_traits<iterator>::difference_type n;

			n = distance (from_itr, to_itr);

			this->m_start = allocator_type::allocate (n);
			this->m_finish = this->m_start + n;
			this->m_end_of_storage = this->m_start + n;
			this->m_size = n;

			iterator curr = m_start;
			while (from_itr != to_itr) {
				copy_construct (curr++, *from_itr++);
			}
		}

		vector (const vector& v) {
            size_type n = v.size ();
            this->m_start = allocator_type::allocate (n);
			this->m_finish = xtl::unititialized_copy (v.begin(), v.end(), m_start);
			this->m_end_of_storage = this->m_finish;
			this->m_size = n;
		}


#if __cplusplus >= 201103L
		//todo: move constructor. c++11
#endif //C++ 11


		~vector() {
			//todo
			xtl::destory(m_start, m_finish);
			allocator_type::deallocate(m_start);
		}



		iterator begin () const {
			return this->m_start;
		}
		iterator end () const {
		    //const_iterator
			return this->m_finish;
		}

		size_type size () const {
		    return m_size;
		}

	protected:
		iterator m_start;
		iterator m_finish;
		iterator m_end_of_storage;
		size_type m_size;
	};
}


#endif /*_XTL_VECOTR_H*/
