/**
 *
 *@Author:  Ke, Xianda
 *@Date: 2014-08-18
 *
 *@Description:
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

#ifndef _XTL_TYPE_TRAIT_H
#define  _XTL_TYPE_TRAIT_H 1

namespace xtl {

	struct _true_type {};
	struct _false_type {};

	template <typename T>
	struct _type_trait {
		typedef  _false_type has_trivial_destructor;
		typedef  _false_type is_pod_type;
	};

	template <>
	struct _type_trait <int> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <unsigned int> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <short> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <char> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <long> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <unsigned long> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <float> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <>
	struct _type_trait <double> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};

	template <typename T>
	struct _type_trait <T*> {
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_pod_type;
	};


	//Xianda's untilities
	template <typename B1, typename B2>
	struct _bool_type_and {
		typedef _false_type type;
	};

	template <>
	struct _bool_type_and <_true_type, _true_type> {
		typedef _true_type  type;
	};

	template <typename B1, typename B2>
	struct _bool_type_or {
		typedef _true_type  type;
	};

	template <>
	struct _bool_type_or <_false_type, _false_type>{
		typedef _false_type type;
	};

}
#endif //_XTL_TYPE_TRAIT_H
