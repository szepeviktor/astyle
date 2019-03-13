// Include this file to activate the leak detector.
#if defined(LEAK_DETECTOR) && defined(_DEBUG) && defined(_MSC_VER)
	#if _MSC_VER > 1900
		#error Use Visual Studio 2015 or lower for leak detector
	#endif
	#include "vld.h"
#endif
