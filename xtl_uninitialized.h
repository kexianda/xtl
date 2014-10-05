#ifndef	_UNINITIALIZED_H_
#define	_UNINITIALIZED_H_ 1

/**
 *	uninitialized_copy
 *	uninitialized_copy_n
 *	uninitialzied_fill
 *	uninitialized_fill_n
 *
 *	memory functions
 *
 *
 * */

#include "xtl_type_trait.h"
#include "xtl_iterator.h"

#include <cstring> //memmove()

namespace xtl {

    //string.h
    void* memmove (void* dest, const void* src, size_t n) {
        //ISO C++ forbids incrementing a pointer of type 'void*'
        char * d = (char*) dest;
        const char * s = (const char*) src;
        if (d < s) {
            while(n--) {
                *d++ = *s++;
            }
        }
        else if (d > s) {
            while(n--) {
                *(d+n) = *(s+n);
            }
        }
        return dest;
    }

}


namespace xtl {



    template <typename InputItr, typename FwdItr>
    FwdItr _unititialized_copy_aux (InputItr first, InputItr last, FwdItr output, xtl::_true_type isPod) {

        typename xtl::iterator_traits<InputItr>::difference_type diff = xtl::distance(first, last);
        typedef typename xtl::iterator_traits<InputItr>::value_type value_type;

        //todo: implement xtl::memmove()
        xtl::memmove (xtl::addressof(*output), xtl::addressof(*first), diff * sizeof(value_type) );
        return (output + diff);
    }

    template <typename InputItr, typename FwdItr>
    FwdItr _unititialized_copy_aux (InputItr first, InputItr last, FwdItr output, xtl::_false_type notPod) {
        FwdItr curr = output;
        for (; first < last; ++first) {
            xtl::copy_construct (xtl::addressof(*curr++), *first);
        }
        return curr;
    }


    template <typename InputItr, typename FwdItr>
    FwdItr unititialized_copy (const InputItr first, const InputItr last, FwdItr output) {

        typedef	typename xtl::iterator_traits<InputItr>::value_type value_type1;
        typedef	typename xtl::iterator_traits<FwdItr>::value_type value_type2;

        typedef typename xtl::_type_trait<value_type1>::is_pod_type type1;
        typedef typename xtl::_type_trait<value_type2>::is_pod_type type2;
        typedef	typename xtl::_bool_type_and<type1, type2>::type dispatch_type;

        return	_unititialized_copy_aux (first, last, output, dispatch_type());
    }


}//end of namespace









#endif //_UNINITIALIZED_H_
