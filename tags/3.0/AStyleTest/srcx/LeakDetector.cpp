// Include this file to activate the leak detector.
#if defined(LEAK_DETECTOR) && defined(_DEBUG) && defined(_MSC_VER)
	#include "vld.h"
#endif
