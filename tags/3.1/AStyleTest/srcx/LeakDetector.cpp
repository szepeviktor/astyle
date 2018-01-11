// Include this file to activate the leak detector.
// It only works for the Win32 (x86) platform
#if defined(LEAK_DETECTOR) && defined(_DEBUG) && defined(_MSC_VER)
	#if _MSC_VER > 1800
		#error Use Visual Studio 2013 or lower for leak detector
	#endif
	#include "vld.h"
#endif
