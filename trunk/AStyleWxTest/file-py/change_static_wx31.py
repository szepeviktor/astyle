#!/usr/bin/python3

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

    NOTE: THIS SCRIPT IS FOR WXWIDGETS VERSION 3.1 AND HIGHER ONLY.
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
wx_paths = [
    #"C:/Programs/wxWidgets-3.1.0_vs2013",
    #"C:/Programs/wxWidgets-3.1.0_vs2015",
    #"C:/Programs/wxWidgets-3.1.0_vs2017",
    "C:/Programs/wxWidgets-3.1.1_vs2017",
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
        process_wxstc_vcxproj_filters_file(wx_path)
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
    if "<PreprocessorDefinitions>" in line and "wxNO_EXCEPTIONS" not in line:
        line = line.replace("_CRT_SECURE_NO_DEPRECATE=1",
                            "wxNO_EXCEPTIONS;_CRT_SECURE_NO_DEPRECATE=1")
    if "<RuntimeLibrary>" in line and "MultiThreadedDLL" in line:
        line = line.replace("MultiThreadedDLL", "MultiThreaded")
    if "<RuntimeTypeInfo>" in line:
        line = line.replace("true", "false")
    return line

# -----------------------------------------------------------------------------

def check_static_config(wx_path):
    """ Check that a "Static" configurartion has been created before update.
        Failure to do this causes bad ".orig" backup files to be saved.
    """
    project_path = "/build/msw/wx_wxscintilla.vcxproj"
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
        updated_file = []           # undated file save area
        lines_changed = 0           # number of lines changed
        is_in_static = False        # is in the Static configuration
        has_static_config = False   # project has a Static configuration
        file_path = file_path.replace('\\', '/')
        if not os.path.exists(file_path):
            libastylewx.system_exit("No file to process: " + file_path)
        # open and process an input file
        with open(file_path, mode='r') as file_in:
            for line in file_in:
                original_line = line
                #! change lines in Static configuration only
                if "ItemDefinitionGroup" in line and "'Static" in line:
                    is_in_static = True
                    has_static_config = True
                if "/ItemDefinitionGroup" in line and is_in_static:
                    is_in_static = False
                if is_in_static:
                    line = change_static_configs(line, file_path)
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
            if line.strip().startswith("LINK_LEXER") and "(lmCPP)" not in line:
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
    project_path = "/build/msw/wx_wxscintilla.vcxproj"
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
                if "\\lexers\\Lex" in line and "\\lexers\\LexCPP" not in line:
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

# -----------------------------------------------------------------------------

def process_wxstc_vcxproj_filters_file(wx_path):
    """ Add CatalogueStatic.cxx file to the wxscintilla project filters file.
        This file is in the build/msw folder.
    """

    catalogue_filter = [
        "    <ClCompile Include=\"..\\..\\src\\stc\\scintilla\\src\\Catalogue.cxx\">",
        "      <Filter>Source Files</Filter>",
        "    </ClCompile>",
        "    <ClCompile Include=\"..\\..\\src\\stc\\scintilla\\src\\CatalogueStatic.cxx\">"]
    updated_file = []           # undated file save area
    lines_changed = 0           # number of lines changed
    project_path = "/build/msw/wx_wxscintilla.vcxproj.filters"
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
                for entry in catalogue_filter:
                    updated_file.append(entry + '\n')
                    lines_changed = 3
                continue
            updated_file.append(line)

    # write the new file
    with open(wx_path + project_path, mode='w') as file_out:
        for line in updated_file:
            file_out.write(line)

    print(lines_changed, "lines in", project_path)

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
    project_path = "/build/msw/wx_setup.props"
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

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
