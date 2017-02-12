#!/usr/bin/python

""" Change wxWidgets Visual Studio .vcxproj files for the Static configuration.
    The Static configuration should have been created as a copy of the Release
    configuration.
    This script will:
    1) Read all of the ".vcxproj" files in the build/msw path and change the
       required Static configuration options.
    2) Read "wx_wxscintilla.vcxproj" and for the Static configuration:
       a) compile CatalogueStatic.cxx instead of Catalogue.cxx.
       b) remove the lexer compiles, except for the cpp lexer (LexCPP.cxx).
    3) Read the Catalogue.cxx file and create a CatalogueStatic.cxx that links
       only the cpp lexer (LexCPP.cxx).
    4) Add the wxWidgets static macros to the setup.props file.

    NOTE: THIS SCRIPT IS FOR WXWIDGETS VERSION 3.0 ONLY.
    NOTE: CHANGE THE wx_paths VARIABLE IN "GLOBAL VARIABLES" BELOW.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import shutil
# local libraries
import libastylewx

# global variables ------------------------------------------------------------

# build/msw paths to be converted
# NOTE: the Visual Studio release is required in the directory name (e.g. vs2015)
wx_paths = [
    #"C:/Programs/wxWidgets-3.0.1_vs2010",
    #"C:/Programs/wxWidgets-3.0.1_vs2012",
    #"C:/Programs/wxWidgets-3.0.2_vs2013",
    "C:/Programs/wxWidgets-3.0.2_vs2015"
]

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
    if os.name != "nt":
        libastylewx.system_exit("\nThis script is for Windows only!")

    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())

    for wx_path in wx_paths:
        print()
        if not check_static_config(wx_path):
            continue
        process_project_files(wx_path)
        print()
        process_wxstc_vcxproj_file(wx_path)
        print()
        process_wxstc_catalogue_file(wx_path)
        print()
        process_wxsetup_props_file(wx_path)

# -----------------------------------------------------------------------------

def change_static_configs(line, file_path):
    """ Change the required variables in a Static configurations.
        Return the updated line.
    """
    #
    # NOTE: "Enable C++ Exceptions" DO NOT REPLACE /EHsc EXCEPTION HANDLING PROPERTY.
    # Microsoft include files are used which require it.
    # It is OK to use wxNO_EXCEPTIONS to remove the wxWidgets exceptions.
    #
    if "<FavorSizeOrSpeed>" in line:
        line = line.replace(">Speed<", ">Size<")
    if "<Optimization>" in line:
        line = line.replace(">MaxSpeed<", ">MinSpace<")
    # DO NOT CHANGE THIS FOR VS2010
    if "_vc11_" in file_path or "_vc12_" in file_path:
        if "<PreprocessorDefinitions>" in line and not "wxNO_EXCEPTIONS" in line:
            line = line.replace("_CRT_SECURE_NO_DEPRECATE=1",
                                "wxNO_EXCEPTIONS;_CRT_SECURE_NO_DEPRECATE=1")
    if "<RuntimeLibrary>" in line and "MultiThreadedDLL" in line:
        line = line.replace("MultiThreadedDLL", "MultiThreaded")
    if "<RuntimeTypeInfo>" in line:
        line = line.replace("true", "false")
    #
    # TESTS FOR VS 2010 ONLY
    # Later relases use macros defined in a "props" file
    # and macros are used for the variables.
    if "_vc10_" in file_path:
        line = change_vs2010_multiple_lines(line)
    # END TESTS FOR VS 2010 ONLY
    #
    return line

# -----------------------------------------------------------------------------

def change_vs2010_multiple_lines(line):
    """ TESTS FOR VS 2010 ONLY
        These tests change data that is defined in a Static ItemDefinitionGroup.
        Later relases use macros defined in a "props" file.
        Return the updated line.
    """
    old_lib = "wxmsw30" + "u_"
    new_lib = "wxmsw30" + "us_"
    old_base = "wxbase30" + "u."
    new_base = "wxbase30" + "us."
    if "<AdditionalIncludeDirectories>" in line:
        line = line.replace("mswu;", "mswus;")
    if "<OutputFile>" in line:
        line = line.replace(old_lib, new_lib)
        line = line.replace(old_base, new_base)
        line = line.replace("wxregexu.", "wxregexus.")
    if "<PrecompiledHeaderOutputFile>" in line:
        line = line.replace("vc_mswu\\", "vc_mswus\\")
        line = line.replace("vc_x64_mswu\\", "vc_x64_mswus\\")
    if "<ProgramDataBaseFileName>" in line:
        line = line.replace(old_lib, new_lib)
    return line

# -----------------------------------------------------------------------------

def change_vs2010_single_line_data(line):
    """ TESTS FOR VS 2010 ONLY
        These tests change data that is defined on a single line.
        Later relases use macros defined in a "props" file.
        Return the updated line.
    """
    old_lib = "wxmsw30" + "u_"
    new_lib = "wxmsw30" + "us_"
    if "<IntDir " in line and "'Static|" in line:
        line = line.replace(">vc_mswu\\", ">vc_mswus\\")
        line = line.replace(">vc_x64_mswu\\", ">vc_x64_mswus\\")
    if "<TargetName " in line and "'Static|" in line:
        line = line.replace(old_lib, new_lib)
    if "<ObjectFileName " in line and "'Static|" in line:
        line = line.replace("vc_mswu\\", "vc_mswus\\")
        line = line.replace("vc_x64_mswu\\", "vc_x64_mswus\\")
    if "<OutDir " in line and "'Static|" in line:
        line = line.replace("\\vc_lib\\", "\\vc_libs\\")
        line = line.replace("\\vc_x64_lib\\", "\\vc_x64_libs\\")

    if "<AdditionalInputs " in line and "'Static|" in line:
        line = line.replace("mswu\\", "mswus\\")
    if "<Command " in line and "'Static|" in line:
        line = line.replace("mswu\\", "mswus\\")
    if "<Message " in line and "'Static|" in line:
        line = line.replace("mswu\\", "mswus\\")
    if "<Outputs " in line and "'Static|" in line:
        line = line.replace("mswu\\", "mswus\\")

    return line

# -----------------------------------------------------------------------------

def check_static_config(wx_path):
    """ Check that a "Static" configurartion has been created before update.
        Failure to do this causes bad ".orig" backup files to be saved.
    """
    if "vs2010" in wx_path:
        project_path = "/build/msw/wx_vc10_wxscintilla.vcxproj"
    elif "vs2012" in wx_path:
        project_path = "/build/msw/wx_vc11_wxscintilla.vcxproj"
    elif "vs2013" in wx_path or "vs2015" in wx_path:
        project_path = "/build/msw/wx_vc12_wxscintilla.vcxproj"
    else:
        libastylewx.system_exit("Cannot determine Visual Studio Version: " + wx_path)
    file_path = wx_path + project_path
    file_path = file_path.replace('\\', '/')
    # read the wxscintilla.vcxproj file
    with open(file_path, mode='r') as file_in:
        for line in file_in:
            #! check for Static configuration in wxscintilla
            if "<Configuration>Static</Configuration>" in line:
                return True
    # no static configuration found
    print(wx_path)
    print("No Static configuration to modify!")
    return False

# -----------------------------------------------------------------------------

def process_project_files(wx_path):
    """ Process all of the "vcxproj" files in the build/msw path.
    """
    # get the project files
    build_path = wx_path + "/build/msw/"
    if not os.path.exists(build_path):
        libastylewx.system_exit("No path to process: " + build_path)
    file_paths = glob.glob(build_path + "*.vcxproj")

    # process the files
    files_changed = 0               # number of files changed
    for file_path in file_paths:
        if not (("vs2010" in wx_path and "_vc10_" in file_path)
                or ("vs2012" in wx_path and "_vc11_" in file_path)
                or ("vs2013" in wx_path and "_vc12_" in file_path)
                or ("vs2015" in wx_path and "_vc12_" in file_path)):
            continue
        updated_file = []           # undated file save area
        lines_changed = 0           # number of lines changed
        is_in_static = False        # is in the Static configuration
        is_vs2010_x64 = False       # is in a VS 2010 Static configuration for Fix
        has_static_config = False   # project has a Static configuration
        file_path = file_path.replace('\\', '/')
        if not os.path.exists(file_path):
            libastylewx.system_exit("No file to process: " + file_path)
        # open and process an input file
        with open(file_path, mode='r') as file_in:
            for line in file_in:
                original_line = line
                #
                # 3.0.1 FIX FOR BUG IN VS 2010 VCXPROJ FILES
                # Precmpiled header files for ALL x64 configurations are
                # incorrectly output to the Win32 directory.
                # This corrects the problem before continuing.
                # 3.1 USES A .PROPS FILE. DON'T KNOW ABOUT 3.0.2.
                # DO NOT MOVE THIS PROCEDURE FROM HERE.
                if "_vc10_" in file_path:
                    if "ItemDefinitionGroup" in line and "|x64'" in line:
                        is_vs2010_x64 = True
                    if "/ItemDefinitionGroup" in line and is_vs2010_x64:
                        is_vs2010_x64 = False
                    if is_vs2010_x64:
                        if ("<PrecompiledHeaderOutputFile>" in line
                                and "vc_msw" in line):
                            line = line.replace("vc_msw", "vc_x64_msw")
                # END VS 2010 FIX
                #
                # 3.0.1 FIX FOR BUG IN VS 2012-2013 VCXPROJ FILES
                # PDB files for the Release, DLL Release, and Static x64
                # platforms always compile even if no changes were made.
                # This is caused by <DebugInformationFormat> set to "None"
                # and <ProgramDataBaseFileName> having a value.
                # This corrects the problem before continuing.
                # THIS IS FIXED IN 3.1. DON'T KNOW ABOUT 3.0.2
                # DO NOT MOVE THIS PROCEDURE FROM HERE.
                if "_vc11_" in file_path or "_vc12_" in file_path:
                    if "<DebugInformationFormat>" in line and "None" in line:
                        line = line.replace("None", "ProgramDatabase")
                # END VS 2012-2013 FIX
                #
                # change lines in Static configuration only
                if "ItemDefinitionGroup" in line and "'Static" in line:
                    is_in_static = True
                    has_static_config = True
                if "/ItemDefinitionGroup" in line and is_in_static:
                    is_in_static = False
                if is_in_static:
                    line = change_static_configs(line, file_path)
                #
                # TESTS FOR VS 2010 ONLY
                if "_vc10_" in file_path:
                    line = change_vs2010_single_line_data(line)
                # END TESTS FOR VS 2010 ONLY
                #
                if line != original_line:
                    lines_changed += 1
                updated_file.append(line)
        # write the updated output file
        with open(file_path, mode='w') as file_out:
            for line_out in updated_file:
                file_out.write(line_out)
        # print debug data
        unused, project_name = os.path.split(file_path)
        if has_static_config:
            print(lines_changed, "lines in", project_name)
        else:
            print("No Static configuration", project_name)
        if lines_changed > 0:
            files_changed += 1
    print(files_changed, "files in", build_path)

# -----------------------------------------------------------------------------

def process_wxstc_catalogue_file(wx_path):
    """ Comment out the static build unused lexers in the wxscintilla Catalogue.cxx file.
        This file is in the src/stc/scintilla/src folder, not the build/msw folder.
        A new file named CatalogueStatic.cxx is created with the commented-out lexers.
    """
    updated_file = []           # undated file save area
    lines_changed = 0           # number of lines changed
    catalogue_path = "/src/stc/scintilla/src/Catalogue.cxx"
    print(wx_path)
    file_path = wx_path + catalogue_path
    file_path = file_path.replace('\\', '/')
    if not os.path.isfile(file_path):
        libastylewx.system_exit("No catalogue file to process: " + file_path)
    with open(file_path, mode='r') as file_in:
        for line in file_in:
            #! remove the link lexer statement in CatalogueStatic
            if line.strip().startswith("LINK_LEXER") and not "(lmCPP)" in line:
                line = line.replace("LINK_LEXER", "//LINK_LEXER")
                lines_changed += 1
            updated_file.append(line)

    static_file = catalogue_path
    static_file = static_file.replace("Catalogue", "CatalogueStatic")
    static_path = wx_path + static_file
    # remove an existing static file
    if os.path.isfile(static_path):
        os.remove(static_path)
    # write the static file
    with open(static_path, mode='w') as file_out:
        for line in updated_file:
            file_out.write(line)
    print(lines_changed, "lines in", static_file)
    print()

# -----------------------------------------------------------------------------

def process_wxstc_vcxproj_file(wx_path):
    """ Change the static unused lexers compile options in the project file.
        This file is in the build/msw folder.
        The static unused lexers are not compiled for the static build.
    """

    catalogue_compile = [
        "    <ClCompile Include=\"..\\..\\src\\stc\\scintilla\\src\\Catalogue.cxx\">",
        "      <ExcludedFromBuild Condition=\"'$(Configuration)'=='Static'\">true</ExcludedFromBuild>",
        "    </ClCompile>",
        "    <ClCompile Include=\"..\\..\\src\\stc\\scintilla\\src\\CatalogueStatic.cxx\">",
        "      <ExcludedFromBuild Condition=\"'$(Configuration)'!='Static'\">true</ExcludedFromBuild>",
        "    </ClCompile>"]
    lexer_exclude = "      <ExcludedFromBuild Condition=\"'$(Configuration)'=='Static'\">true</ExcludedFromBuild>"

    updated_file = []           # undated file save area
    lines_changed = 0           # number of lines changed
    if "vs2010" in wx_path:
        project_path = "/build/msw/wx_vc10_wxscintilla.vcxproj"
    elif "vs2012" in wx_path:
        project_path = "/build/msw/wx_vc11_wxscintilla.vcxproj"
    elif "vs2013" in wx_path or "vs2015" in wx_path:
        project_path = "/build/msw/wx_vc12_wxscintilla.vcxproj"
    else:
        libastylewx.system_exit("Cannot determine Visual Studio Version: " + wx_path)
    orig_path = project_path + ".orig"
    print(wx_path)
    file_path = wx_path + orig_path
    file_path = file_path.replace('\\', '/')
    if not os.path.isfile(file_path):
        shutil.copyfile(wx_path + project_path, file_path)
    # read the .orig file
    with open(file_path, mode='r') as file_in:
        for line in file_in:
            #! check for Catalogue.cxx in wxscintilla
            if "<ClCompile Include=" in line and "Catalogue.cxx" in line:
                for catalogue_new in catalogue_compile:
                    lines_changed += 1
                    updated_file.append(catalogue_new + '\n')
                continue
            #! check for unused static build lexers in wxscintilla
            if "<ClCompile Include=" in line:
                if "\\lexers\\Lex" in line and not "\\lexers\\LexCPP" in line:
                    end = line.find(" />")
                    if end != -1:
                        lines_changed += 1
                        line = line[:end] + ">\n"
                        updated_file.append(line)
                        updated_file.append(lexer_exclude + '\n')
                        line = "    </ClCompile>\n"
            updated_file.append(line)

    # write the new file
    with open(wx_path + project_path, mode='w') as file_out:
        for line in updated_file:
            file_out.write(line)

    print(lines_changed, "lines in", project_path)
    print()

# -----------------------------------------------------------------------------

def process_wxsetup_props_file(wx_path):
    """ Add the static wxWidgets variables to the wx_setup.props file.
        This file is in the build/msw folder.
    """

    suffix_additions = [
        "",
        "  <PropertyGroup Label=\"UserMacros\" Condition=\"'$(Configuration)'=='Static' and '$(CharacterSet)'=='Unicode'\">",
        "    <wxSuffix>us</wxSuffix>",
        "  </PropertyGroup>",
        "  <PropertyGroup Label=\"UserMacros\" Condition=\"'$(Configuration)'=='Static' and '$(CharacterSet)'!='Unicode'\">",
        "    <wxSuffix>s</wxSuffix>",
        "  </PropertyGroup>",
        "  <PropertyGroup Label=\"UserMacros\" Condition=\"'$(Configuration)'=='Static'\">",
        "    <wxCfg>s</wxCfg>",
        "  </PropertyGroup>",
        ""]

    directory_additions = [
        "",
        "  <PropertyGroup Label=\"UserMacros\" Condition=\"'$(Configuration)'=='Static'\">",
        "    <wxOutDir>..\\..\\lib\\$(wxCompilerPrefix)$(wxArchSuffix)_lib$(wxCfg)\\</wxOutDir>",
        "  </PropertyGroup>",
        "  <PropertyGroup Label=\"UserMacros\" Condition=\"'$(Configuration)'=='Static'\">",
        "    <wxIntRootDir>$(wxCompilerPrefix)$(wxArchSuffix)_$(wxToolkitPrefix)$(wxSuffix)\\</wxIntRootDir>",
        "  </PropertyGroup>",
        ""]

    updated_file = []           # undated file save area
    wxsuffix_stmts = 0          # number of <wxSuffix> statements
    wxintrootdir_stmts = 0      # number of <wxIntRootDir> statements
    lines_changed = 0           # number of lines changed
    # determine the file name
    if "vs2010" in wx_path:		# vs2010 does NOT have a setup.props
        return
    elif "vs2012" in wx_path:
        project_path = "/build/msw/wx_vc11_wx_setup.props"
    elif "vs2013" in wx_path or "vs2015" in wx_path:
        project_path = "/build/msw/wx_vc12_wx_setup.props"
    else:
        libastylewx.system_exit("Cannot determine Visual Studio Version: " + wx_path)
    orig_path = project_path + ".orig"
    print(wx_path)
    file_path = wx_path + orig_path
    file_path = file_path.replace('\\', '/')
    if not os.path.isfile(file_path):
        shutil.copyfile(wx_path + project_path, file_path)
    # read the .orig file
    with open(file_path, mode='r') as file_in:
        for line in file_in:
            #! check for end of <wxSuffix> statements
            if "<wxSuffix>" in line:
                wxsuffix_stmts += 1
            if "</PropertyGroup>" in line and wxsuffix_stmts == 4:
                wxsuffix_stmts = 9			# don't do it again
                updated_file.append(line)
                for setup_new in suffix_additions:
                    lines_changed += 1
                    updated_file.append(setup_new + '\n')
                continue
            #! check for end of <wxIntRootDir> statements
            if "<wxIntRootDir>" in line:
                wxintrootdir_stmts += 1
            if "</PropertyGroup>" in line and wxintrootdir_stmts == 4:
                wxintrootdir_stmts = 9		# don't do it again
                updated_file.append(line)
                for setup_new in directory_additions:
                    lines_changed += 1
                    updated_file.append(setup_new + '\n')
                continue

            updated_file.append(line)

    # write the new file
    with open(wx_path + project_path, mode='w') as file_out:
        for line in updated_file:
            file_out.write(line)

    print(lines_changed, "lines in", project_path)
    print()

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
