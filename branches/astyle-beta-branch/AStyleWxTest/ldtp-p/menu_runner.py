# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import sys
import unittest
#! NOTE: Local scripts importing ldtp should be imported after ldtp below.
#!       This will assure that the messages are displayed before importing.

# check for python 2.7 before importing ldtp
version = " {0}.{1}.{2}  ".format(sys.version_info[0],
                                    sys.version_info[1],
                                    sys.version_info[2])
print("Python version " + version)
if not sys.version_info[0] == 2 or not sys.version_info[1] == 7:
    print("\nThis script requires Python version 2.7.")
    sys.exit(1)

# import ldtp and display warning messages
print("Importing ldtp")
print()
if os.name == "nt":
    print("This test MUST be run as an administrator.")
    print("Otherwise the WinLdtpService will not work.")
    print("And an \"Access is denied\" exception will be thrown.")
print("Do NOT use the mouse while this test is running.")
try:
    import ldtp
except:
    # 6 unhandled exceptions will be displayed before this
    print("\nLdtp was not imported.")
    print("This test MUST be run as an administrator.")
    sys.exit(1)

#! import these AFTER importing ldtp
import libastylewx      # local script
import menu_test1       # local script
import menu_test2       # local script

# compile astylewx executable
if os.name == "nt":
    print("\nCompiling astylewx")
    libastylewx.compile_windows_astylewx_exe("DLL Debug")
else:
    exepath = (libastylewx.get_astylewx_path()
               + "/build/cb-gcc/"
               + "wx" + libastylewx.WX_RELEASE
               + "/bin/astylewxd")
    if not os.path.exists(exepath):
        libastylewx.terminate_program("\nastylewx has not been compiled: " + exepath)

# menu_test1
libastylewx.launch_astylewx_ldtp()
suite1 = unittest.TestLoader().loadTestsFromTestCase(menu_test1.MenuTest1)
unittest.TextTestRunner(verbosity=2).run(suite1)
libastylewx.close_astylewx_ldtp()

# menu_test2
libastylewx.launch_astylewx_ldtp()
suite2 = unittest.TestLoader().loadTestsFromTestCase(menu_test2.MenuTest2)
unittest.TextTestRunner(verbosity=2).run(suite2)
libastylewx.close_astylewx_ldtp()

# end tests
libastylewx.print_separator()
#print("Test totals")
#tests_run_case1 = len(unittest.TestLoader().getTestCaseNames(menu_test1.MenuTest1))
#tests_run_case2 = len(unittest.TestLoader().getTestCaseNames(menu_test2.MenuTest2))
#print('Test case 1: ' + str(tests_run_case1))
#print('Test case 2: ' + str(tests_run_case2))
#libastylewx.print_separator()
