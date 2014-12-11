// *INDENT-OFF*
// Included this file to activate the leak detector.
#if defined(LEAK_DETECTOR) && defined(_DEBUG) && defined(_MSC_VER)
	#include "vld.h"
	// THE LEAK DETECTOR IS WORKING WITH VERSION 2.4RC2
	// temporary check because of problem with VS 2013
	//#if _MSC_VER >= 1800
	//	#error - Leak detector works only with Visual Studio 2012 or lower
	//#endif
#endif
// *INDENT-ON*
