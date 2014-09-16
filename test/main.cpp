

#if defined(_WIN32) || defined(_WIN64)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif //Windows CRT GBD

#ifdef __linux__
#include <cstdlib>
#include <mcheck.h>
#endif //__linux__


#include <iostream>
#include "test.h"


int main () {

	#ifdef __linux__
	//$./test.out
	//$mtrace test.out memcheck.o > report.o
	setenv ("MALLOC_TRACE", "memcheck.o", 1);
	mtrace();
	#endif //__linux__


	xtl_memeory_test::test_xtl_Memory();

	xtl_vector_test::test();



	#ifdef __linux__
	//muntrace();
	#endif //__linux__

	#if (defined(_WIN32) || defined(_WIN64)) && defined(_DEBUG)
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT); //_CRT_WARN
	_CrtDumpMemoryLeaks();
	#endif //Windows CRT GBD	return 0;
}
