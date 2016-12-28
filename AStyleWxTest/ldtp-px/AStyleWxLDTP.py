#! /usr/bin/python2
""" ON WINDOWS THIS SCRIPT MUST BE RUN WITH ADMINISTRATIVE PRIVLEDGES.
    If this is not done a message will display that "WinLdtpService has stopped working".
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import sys
# from time import sleep

# global statements to import ldtp --------------------------------------------

# must check for python 2.7 before importing ldtp
version = " {0}.{1}.{2}  ".format(sys.version_info[0],
                                  sys.version_info[1],
                                  sys.version_info[2])
print("python version " + version)
if not sys.version_info[0] == 2 or not sys.version_info[1] == 7:
    print("This script requires version 2.7")
    print("The script has terminated!")
    sys.exit(1)

print("Importing ldtp")
try:
    import ldtp
except:
    print("ldtp was not imported")
    print("This script must be run as an administrator")
    print("The script has terminated!")
    exit(1)

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    if os.name == "nt":
        exepath = "C:/Users/jimp/Projects/AStyleWx/build/vs2013_3.0/debug/AStyleWxd.exe"
    else:
        exepath = "../../AStyleWx/build/cb-gcc/wx3.0/bin/astylewxd"
    exepath = exepath.replace('/', os.sep)

    #print(sys.path[0])
    os.chdir(sys.path[0])

    if not os.path.exists(exepath):
        print("Cannot find executable: " + exepath)
        print("The script has terminated!")
        sys.exit(1)

    print("Launching AStyleWx")
    try:
        ldtp.launchapp(exepath)
    except ldtp.client_exception.LdtpExecutionError as err:
        print("Error in launchapp: " + exepath)
        print(err)
        print("The script has terminated!")
        sys.exit(1)
    if not ldtp.waittillguiexist('*AStyleWx'):
        print("Error in waittillguiexist")
        print("The script has terminated!")
        sys.exit(1)

    print('\nFile')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuFile'))
    print('\nEdit')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuEdit'))
    print('\nSearch')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuSearch'))
    print('\nView')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuView'))
    print('\nTools')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuTools'))
    print('\nHelp')
    print(ldtp.listsubmenus('frmAStyleWx', 'mnuHelp'))
    print()

    print("Closing AStyleWx")
    ldtp.selectmenuitem('frmAStyleWx', 'mnuFile;mnuExit')
    if not ldtp.waittillguinotexist('*AStyleWx'):
        print("Error in waittillguinotexist")
        print("The script has terminated!")
        sys.exit(1)

# -----------------------------------------------------------------------------

#selectmenuitem('*gedit', 'mnuFile;mnuOpen')

#~ from ldtp import *
#~ launchapp('notepad')
#~ waittillguiexist('*-Notepad')
#~ selectmenuitem('*-Notepad', 'mnuFile;mnuExit')
#~ waittillguinotexist('*-Notepad')



#~ frm = ooldtp.context('*gedit')
#~ frm.waittillguiexist()
#~ txt_field = frm.getchild('txt1')
#~ txt_field.enterstring('Hello world!<return>bye<return>')
#~ ldtp.imagecapture('*gedit', '/tmp/foo.png')
#~ mnu_quit = frm.getchild('mnuQuit')
#~ mnu_quit.selectmenuitem()
#~ alert = ooldtp.context('Question')
#~ alert.waittillguiexist()
#~ btn = alert.getchild('btnClosewithoutSaving')
#~ btn.click()
#~ frm.waittillguinotexist()

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    print("End of script!")
    sys.exit(0)

# -----------------------------------------------------------------------------
