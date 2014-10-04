/**
 *	@Author: Ke, Xianda
 *  @Date: 2014-08-18
 *
 *  Follow stl standard
 *
 * */

/*
 *
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
#ifndef _XTL_ITERATOR_H
#define _XTL_ITERATOR_H 1


/**
 * iterator base
 * */
namespace xtl {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


    template <typename T, typename Category, typename Distance = ptrdiff_t>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef T*			pointer;
		typedef T&			reference;
		typedef Distance	difference_type;
	};


	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type		value_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type	difference_type;
	};

	//partially specializtion for pointer type
	template <typename T>
	struct iterator_traits <T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef ptrdiff_t					difference_type;
	};

	//partially specializtion for const pointer type
	template <typename T>
	struct iterator_traits <const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef ptrdiff_t					difference_type;
	};

}//end of namespace


//functions for iterator
namespace  xtl {

	//interanl use
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	get_iterator_category () {
		typedef typename iterator_traits<Iterator>::iterator_category	 Category;
		return Category ();
	}


	template <typename Iterator>
	inline typename iterator_traits<Iterator>::pointer
	get_pointer (const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::pointer> (0);
	}


	template <typename Input_Iterator>
	inline typename iterator_traits<Input_Iterator>::difference_type
	_distance (Input_Iterator input_begin, Input_Iterator input_last,
				input_iterator_tag) {
		typename iterator_traits<Input_Iterator>::difference_type dist = 0;
		while (input_begin != input_last) {
			++dist;
		}
		return dist;
	}


	template <typename Random_Iterator>
	inline typename iterator_traits<Random_Iterator>::difference_type
	_distance (Random_Iterator rand_begin, Random_Iterator rand_last,
		   		random_access_iterator_tag) {
		return rand_last - rand_begin;
	}

	template <typename Input_Iterator>
	inline typename iterator_traits<Input_Iterator>::difference_type
	distance (Input_Iterator input_begin, Input_Iterator input_last) {
	    //dispatcher
		return _distance (input_begin, input_last, get_iterator_category<Input_Iterator>());
	}

}
/**
 *
 *	reverse_iterator
 * */
namespace xtl {

	//reverse_iterator
	template <class Iterator>
	class reverse_iterator {
	public:
		typedef Iterator	iterator_type;

		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
        typedef typename iterator_traits<Iterator>::value_type 			value_type;
        typedef	typename iterator_traits<Iterator>::pointer				pointer;
        typedef	typename iterator_traits<Iterator>::reference			reference;
	  	typedef typename iterator_traits<Iterator>::difference_type		difference_type;

		reverse_iterator () : current() {}

		explicit reverse_iterator (Iterator itr) : current (itr) {}

		reverse_iterator (const reverse_iterator& ri) : current(ri.base()) {}

		//if _Itr can convert to Iterator //todo
		//template <_Itr>
		//reverse_iterator (const reverse_iterator<_Itr>& ri) : current(ri.base()) {}

		iterator_type base () const { return current;}

	public:
		reference operator* () {
			iterator_type tmp = current;
			return * (--tmp);
		}

		pointer operator->() {
			return &(*current);
		}

		reverse_iterator & operator++() {
			--current;
			return *this;
		}

		reverse_iterator & operator++(int) {
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator & operator--() {
			++current;
			return *this;
		}

		reverse_iterator & operator--(int) {
			--current;
			return *this;
		}

		reverse_iterator operator+(difference_type n) {
			return reverse_iterator (current - n);
		}

		reverse_iterator & operator+=(difference_type n) {
			current -= n;
			return *this;
        }

		reverse_iterator operator-(difference_type n) {
			return reverse_iterator (current + n);
		}

		reverse_iterator & operator-=(difference_type n) {
			current += n;
			return *this;
        }

		reference operator[](difference_type n) {
			operator* (current - n);
		}

	protected:
		Iterator current;
	};


	//template <typename Iterator>
	//typename iterator_traits<Iterator>::
	//inline	operator+()

}//end of reverse_iterator

#endif // _XTL_ITERATOR_H
