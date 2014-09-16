/**
 *
 *@Author:  Ke, Xianda 
 *@Date: 2014-08-18
 *
 *@Description:  Just for fun.
 *
 **/

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
#ifndef _XTL_CONSTRUCT_H
#define _XTL_CONSTRUCT_H

#include <new> //replacement new

#include "xtl_type_trait.h"

namespace xtl {
	
	template <typename T>
	inline void construct (T* p){
		::new (p) T();
	}
	
	template <typename T>
	inline void copy_construct (T* p, const T& value) {
		::new (p) T (value);
	} 
	
	template <typename T>
	inline void _destory (T* p) {
		//delete p;
		p->~T();
	}
	
	template <typename FwdItr>
	inline void _destory_aux (FwdItr first, FwdItr last, _true_type) {
		//do nothing
	}
	
	template <typename FwdItr>
	inline void _destory_aux (FwdItr first, FwdItr last,  _false_type) {
		for (; first < last; ++first) {
			_destory (& *first);
		}
	} 
	
	template <typename FwdItr, typename T>
	inline void _destory_aux (FwdItr first, FwdItr last, T*) {
		typedef typename _type_trait<T>::has_trivial_destructor trivial_destructor;
		_destory_aux (first, last, trivial_destructor());
	}
	
	template <typename FwdItr>
	inline void destory (FwdItr first, FwdItr last) {
		_destory_aux (first, last, &*first);
	}
	
}
#endif // _XTL_CONSTRUCT_H

