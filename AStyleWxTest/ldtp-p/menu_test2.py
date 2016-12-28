"""
Check menu enabled or disabled when there is no editor open.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastylewx      # local scrip
import ldtp             # ldtp script
import os
import unittest


class MenuTest2(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        libastylewx.print_separator()
        print("Checking menu sans editor")
        # close the open pane
        ldtp.selectmenuitem('frmAStyleWx', 'mnuFile;mnuClose')
        # linux must open a menu so that OnMenuOpen() in astylewx will be called
        libastylewx.activate_linux_menus()

    def setUp(self):
        """Display an ERROR if the pane is not closed.
           It is closed in setUpClass() but cannot be checked there because
           unittest asserts must be called with a MenuTest2 instance.
           In practice, this assert should not fail.
           It adds to the run time and may be commented out.
        """
        # check linux only since it runs much faster than windows
        if not os.name == "nt":
            pane_exists = ldtp.guiexist('frmAStyleWx', 'panecontrol')
            self.assertFalse(pane_exists, 'The panecontrol should not exist')

    #@classmethod
    #def tearDownClass(self):

    ## FILE MENU

    def test_file_new(self):
        file_new_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuNew')
        self.assertTrue(file_new_enabled)

    def test_file_open(self):
        file_open_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuOpen')
        self.assertTrue(file_open_enabled)

    def test_file_close(self):
        file_close_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuClose')
        self.assertFalse(file_close_enabled)

    def test_file_save(self):
        file_save_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuSave')
        self.assertFalse(file_save_enabled)

    def test_file_saveas(self):
        file_saveas_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuSave As')
        self.assertFalse(file_saveas_enabled)

    def test_file_exit(self):
        file_exit_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuFile;mnuExit')
        self.assertTrue(file_exit_enabled)

    ## EDIT MENU

    def test_edit_undo(self):
        edit_undo_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuUndo')
        self.assertFalse(edit_undo_enabled)

    def test_edit_redo(self):
        edit_redo_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuRedo')
        self.assertFalse(edit_redo_enabled)

    def test_edit_cut(self):
        edit_cut_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuCut')
        self.assertFalse(edit_cut_enabled)

    def test_edit_copy(self):
        edit_copy_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuCopy')
        self.assertFalse(edit_copy_enabled)

    def test_edit_paste(self):
        # paste may or may not be enabled depending on if something is in the clipboard
        # the only thing that can be checked for sure is if the menu exists
        edit_paste_exists = ldtp.doesmenuitemexist('frmAStyleWx', 'mnuEdit;mnuPaste')
        self.assertTrue(edit_paste_exists)

    def test_edit_selectall(self):
        edit_selectall_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuSelectAll')
        self.assertFalse(edit_selectall_enabled)

    def test_edit_selecttostart(self):
        edit_selecttostart_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuSelecttoStart')
        self.assertFalse(edit_selecttostart_enabled)

    def test_edit_selecttoend(self):
        edit_selecttoend_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuSelecttoEnd')
        self.assertFalse(edit_selecttoend_enabled)

    def test_edit_selectblock(self):
        edit_selectblock_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuSelectBlock')
        self.assertFalse(edit_selectblock_enabled)

    def test_edit_increaseindent(self):
        edit_increaseindent_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuIncreaseIndent')
        self.assertFalse(edit_increaseindent_enabled)

    def test_edit_decreaseindent(self):
        edit_decreaseindent_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuDecreaseIndent')
        self.assertFalse(edit_decreaseindent_enabled)

    def test_edit_options(self):
        edit_options_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuEdit;mnuOptions')
        self.assertTrue(edit_options_enabled)

    ## SEARCH MENU

    def test_search_find(self):
        search_find_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuFind')
        self.assertFalse(search_find_enabled)

    def test_search_findnext(self):
        search_findnext_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuFindNext')
        self.assertFalse(search_findnext_enabled)

    def test_search_findprevious(self):
        search_findprevious_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuFindPrevious')
        self.assertFalse(search_findprevious_enabled)

    def test_search_gotoline(self):
        search_gotoline_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuGotoLine')
        self.assertFalse(search_gotoline_enabled)

    def test_search_nextbookmark(self):
        search_nextbookmark_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuNextBookmark')
        self.assertFalse(search_nextbookmark_enabled)

    def test_search_previousbookmark(self):
        search_previousbookmark_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuPreviousBookmark')
        self.assertFalse(search_previousbookmark_enabled)

    def test_search_togglebookmark(self):
        search_togglebookmark_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuToggleBookmark')
        self.assertFalse(search_togglebookmark_enabled)

    def test_search_clearallbookmarks(self):
        search_clearallbookmarks_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuSearch;mnuClearAllBookmarks')
        self.assertFalse(search_clearallbookmarks_enabled)

    ## VIEW MENU

    def test_view_linenumbers(self):
        view_linenumbers_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuLineNumbers')
        self.assertTrue(view_linenumbers_enabled)

    def test_view_margin(self):
        view_margin_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuMargin')
        self.assertTrue(view_margin_enabled)

    def test_view_whitespace(self):
        view_whitespace_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuWhitespace')
        self.assertTrue(view_whitespace_enabled)

    def test_view_activeline(self):
        view_activeline_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuActiveLine')
        self.assertTrue(view_activeline_enabled)

    def test_view_indentguides(self):
        view_indentguides_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuIndentGuides')
        self.assertTrue(view_indentguides_enabled)

    def test_view_endofline(self):
        view_endofline_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuEndofLine')
        self.assertTrue(view_endofline_enabled)

    def test_view_wordwrap(self):
        view_wordwrap_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuWordWrap')
        self.assertTrue(view_wordwrap_enabled)

    def test_view_toolbar(self):
        view_toolbar_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuToolBar')
        self.assertTrue(view_toolbar_enabled)

    def test_view_statusbar(self):
        view_statusbar_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuView;mnuStatusBar')
        self.assertTrue(view_statusbar_enabled)

    ## TOOLS MENU

    def test_tools_filemode(self):
        tools_filemode_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuFileMode')
        self.assertTrue(tools_filemode_enabled)

    def test_tools_lineends(self):
        tools_lineend_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuLineEnds')
        self.assertTrue(tools_lineend_enabled)

    def test_tools_formatselection(self):
        tools_formatselection_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuFormatSelection')
        self.assertFalse(tools_formatselection_enabled)

    def test_tools_formatsource(self):
        tools_formatsource_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuFormatSource')
        self.assertFalse(tools_formatsource_enabled)

    def test_tools_tabstospaces(self):
        tools_tabstospaces_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuTabstoSpaces')
        self.assertFalse(tools_tabstospaces_enabled)

    def test_tools_striptrailingspaces(self):
        tools_striptrailingspaces_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuStripTrailingSpaces')
        self.assertFalse(tools_striptrailingspaces_enabled)

    def test_tools_astylesettings(self):
        tools_astylesettings_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuAStyleSettings')
        self.assertTrue(tools_astylesettings_enabled)

    def test_tools_testoptions(self):
        tools_testoptions_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuTestOptions')
        self.assertTrue(tools_testoptions_enabled)

    def test_tools_astyleoptions(self):
        tools_astyleoptions_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuTools;mnuAStyleOptions')
        self.assertTrue(tools_astyleoptions_enabled)

    ## HELP MENU

    def test_help_help(self):
        help_help_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuHelp;mnuHelp')
        self.assertTrue(help_help_enabled)

    def test_help_about(self):
        help_about_enabled = ldtp.menuitemenabled('frmAStyleWx', 'mnuHelp;mnuAbout')
        self.assertTrue(help_about_enabled)
