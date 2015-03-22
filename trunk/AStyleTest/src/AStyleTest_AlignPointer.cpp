//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//-------------------------------------------------------------------------
// AStyle Align Pointer None
//-------------------------------------------------------------------------

TEST(AlignPointerNone, LongOption)
{
	// pointers and references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Tabs)
{
	// test with tab separators
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, AddressOf)
{
	// "address of" operator should NOT be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Dereference1)
{
	// dereference should NOT be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char**)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Dereference3)
{
	// a dereference following a cast should not be space padded
	char text[] =
		"\nvoid Foo();\n"
		"{\n"
		"    wxImageHandler *handler = (wxImageHandler *)\n"
		"                              *node;\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream *_err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream *_err = NULL;\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, GlobalDeclarations)
{
	// test with global declarations
	char text[] =
		"\n// function declarations\n"
		"void *foo(char* fooBar);\n"
		"char&bar(char&);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Cast1)
{
	// cast should not be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Cast2)
{
	// cast should not be changed
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void * fooBar);\n"
		"void foo(void **, void**);\n"
		"void foo(wxCommandEvent &);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, ConvertTabs)
{
	// test tab conversion
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox	*channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void			*userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox   *channel;\n"
		"    wxTextCtrl  *filename;\n"
		"    char        *   stamp;\n"
		"    void            *userData;\n"
		"}\n";
	char options[] = "convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Paren)
{
	// test pointer recognition in a paren
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject* p  = pm->GetProject())\n"
		"        getBar();\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"    if(cbProject  *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, PointerToPointer1)
{
	// test pointer to pointer
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, PointerToPointer2)
{
	// test pointer to pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, PointerToPointer3)
{
	// test pointer to pointer with space separation
	// these do not change because of a multiply then a dereference (a * *b)
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    * *bar1;\n"
		"    char  * *  bar1;\n"
		"    char * *    bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, EndOfLine1)
{
	// test pointer at end of line
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void*      // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char**\n"
		"bar() {}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, EndOfLine3)
{
	// test reference at end of line
	char text[] =
		"\nwxPdfColour&\n"
		"wxPdfColour::operator= ( const wxPdfColour&\n"
		"                         colour )\n"
		"{}";
	char options[] = "pad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, BeginLine1)
{
	// a pointer begins the line
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, BeginLine2)
{
	// a pointer begins the line and is followed by a comment
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;      //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;       //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Comment1)
{
	// test pointer with comment after
	char text[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, Comment2)
{
	// test pointer with comment after and a default variable
	char text[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu* /*menu*/,\n"
		"                     const FileTreeData* /*data*/ = 0)\n"
		"{}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, BeforeEqual)
{
	// don't convert '& =' to '&='
	char text[] =
		"\nvoid SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString  &  = _(\",\"));\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, OperatorOverload)
{
	// test pointer with overloaded operator
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, ConversionOperator)
{
	// test pointer with conversion operator
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, ScopeResolution)
{
	// should not change a scope resolution operator
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, PadParenOutside)
{
	// should not change scope resolution operator
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char options[] = "pad-paren-out";
	char* textOut1 = AStyleMain(text, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut1;
	delete[] textOut;
}

TEST(AlignPointerNone, PadParenEmpty)
{
	// an empty pad paren should not change align
	char text[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T *() const {\n"
		"        return (T *) 0;\n"
		"    }\n"
		"};";
	char options[] = "pad-paren-out";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char text[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, CppCLI)
{
	// should not change a C++/CLI file.
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, CSharp)
{
	// should not change a C# file.
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, RvalueReference)
{
	// test on a rvalue reference.
	char text[] =
		"\nMemoryBlock&& f(MemoryBlock &&block)\n"
		"{\n"
		"    A&& a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, RvalueReferenceDeclaration1)
{
	// test on a rvalue reference in a declaration.
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int&&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo2(int && );\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, RvalueReferenceDeclaration2)
{
	// test on a rvalue reference in a declaration.
	char text[] =
		"\nstruct A {\n"
		"    A& operator=( const A&& );\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, RvalueReferenceOperatorOverload)
{
	// test on a rvalue reference in a declaration.
	char text[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test && rhs);\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, ClosingFollowingChar)
{
	// Following a * is not closed for templates.
	char text[] =
		"\n"
		"void Foo(char *, char * );     // comment\n"
		"void Foo(char *, char *);      // comment\n"
		"\n"
		"vector< ParseTree* > m_TreeStack;    // comment\n"
		"vector<ParseTree*> m_TreeStack;      // comment";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, TrailingReferenceType)
{
	// Using a trailing reference type in a function declaration.
	// Should not change the alignment.
	char text[] =
		"\n"
		"auto method(int x)->int&;\n"
		"auto method(int x)->int &;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerNone, SquareBrackets)
{
	// A * in brackets is an operator.
	// Should not change the alignment.
	char text[] =
		"\nclass Matrix\n"
		"{\n"
		"    Matrix() : data(new ValueType[m * n]) {}\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer Type
//-------------------------------------------------------------------------

TEST(AlignPointerType, LongOption)
{
	// test align pointer=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string* bar;     // comment\n"
		"    const string*   bar;   // comment\n"
		"    const string*   bar;   // comment\n"
		"    const string* bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, ShortOption)
{
	// test align pointer=type short option
	char textIn[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string *bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string* bar;\n"
		"}\n";
	char options[] = "-k1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, FromCentered)
{
	// test align pointer=type when input is centered
	// a space is deleted in certain circumstances
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;     // remove space\n"
		"    const string  * bar;    // don't remove\n"
		"    const string *  bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string ** bar;    // remove space\n"
		"    const string  ** bar;   // don't remove\n"
		"    const string **  bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string & bar;     // remove space\n"
		"    const string  & bar;    // don't remove\n"
		"    const string &  bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;      // remove space\n"
		"    const string*   bar;    // don't remove\n"
		"    const string*   bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"\n"
		"    const string** bar;     // remove space\n"
		"    const string**   bar;   // don't remove\n"
		"    const string**   bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"\n"
		"    const string& bar;      // remove space\n"
		"    const string&   bar;    // don't remove\n"
		"    const string&   bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char*	bar;\n"
		"    const char*		bar;\n"
		"    const char*		bar;\n"
		"    const char*				bar;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Dereference1)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char**)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Dereference3)
{
	// a dereference following a cast should not be space padded
	char text[] =
		"\nvoid Foo();\n"
		"{\n"
		"    wxImageHandler* handler = (wxImageHandler*)\n"
		"                              *node;\n"
		"}";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Dereference4)
{
	// a dereference following a question mark should not be attached
	char text[] =
		"\n"
		"Config newCfg = { somePtr ? *somePtr : DEFAULT_ENUM_VALUE,\n"
		"                  otherPtr ? *otherPtr : std::wstring()\n"
		"                };";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream *_err = &cerr;\n"
		"ASConsole *g_console;\n"
		"stringstream *_err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void *foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void* foo(char* fooBar);\n"
		"char& bar(char&);\n";;
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Cast1)
{
	// cast should not be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Cast2)
{
	// cast should not be space padded
	char textIn[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void * fooBar);\n";
	char text[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void* fooBar, void* fooBar);\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox	*channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void			*userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*   channel;\n"
		"    wxTextCtrl*  filename;\n"
		"    char*           stamp;\n"
		"    void*            userData;\n"
		"}\n";
	char options[] = "align-pointer=type, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject* p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PointerToPointer1)
{
	// test pointer to pointer
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char**    bar1;\n"
		"    char**    bar1;\n"
		"    char**    bar1;\n"
		"    char**		bar1;\n"
		"    char**				bar1;\n"
		"    char** bar1;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PointerToPointer2)
{
	// test pointer to pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PointerToPointer3)
{
	// test pointer to pointer with space separation
	// these do not change because of a multiply then a dereference (a * *b)
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    * *bar1;\n"
		"    char  * *  bar1;\n"
		"    char* *    bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char    * *bar1;\n"
		"    char  * *  bar1;\n"
		"    char* *    bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char&\n"
		"bar() {}\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char&\n"
		"bar() {}\n"
		"\n"
		"void*      // comment\n"
		"foo() {}\n"
		"\n"
		"void**     /* comment */\n"
		"foo() {}\n"
		"\n"
		"char**\n"
		"bar() {}\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, EndOfLine3)
{
	// test reference at end of line
	char text[] =
		"\nwxPdfColour&\n"
		"wxPdfColour::operator= ( const wxPdfColour&\n"
		"                         colour )\n"
		"{}";
	char options[] = "align-pointer=type, pad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, BeginLine1)
{
	// a pointer begins the line
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    ** Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    * Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, BeginLine2)
{
	// a pointer begins the line and is followed by a comment
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;      //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;       //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    ** Names1;     //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    * Names4;      //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Comment1)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList* /*keyword*/,\n"
		"         WordList** /*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Comment2)
{
	// test pointer with comment after and a default variable
	char textIn[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu * /*menu*/,\n"
		"                     const FileTreeData * /*data*/ = 0)\n"
		"{}";
	char text[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu* /*menu*/,\n"
		"                     const FileTreeData* /*data*/ = 0)\n"
		"{}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, BeforeEqual)
{
	// don't convert '& =' to '&='
	char textIn[] =
		"\nvoid SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString  &  = _(\",\"));\n";
	char text[] =
		"\nvoid SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString&    = _(\",\"));\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T* operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef& () { return fEvent; }\n"
		"operator HIRect* () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef& ();\n"
		"operator HIRect* ();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect* pr   = (HIRect*) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, ScopeResolution)
{
	// should not pad a scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"} cv;\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, FunctionPointer)
{
	// test char* in a function pointer
	char textIn[] =
		"\nvoid STDCALL Foo(char * (STDCALL * fpAlloc)(unsigned long));";
	char text[] =
		"\nvoid STDCALL Foo(char* (STDCALL* fpAlloc)(unsigned long));";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PadParenOutside)
{
	// should not change scope resolution operator
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR)& isDynamic},\n"
		"        { Maxtext,  (LPTSTR)& maxText},\n"
		"        { IconID,   (LPTSTR)& iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=type, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut1;
	delete[] textOut;
}

TEST(AlignPointerType, PadParenEmpty)
{
	// an empty pad paren should align on the type
	char textIn[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T *() const {\n"
		"        return (T *) 0;\n"
		"    }\n"
		"};";
	char text[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T* () const {\n"
		"        return (T*) 0;\n"
		"    }\n"
		"};";
	char options[] = "align-pointer=type, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State* L, int idx);\n"
		"LUA_API const void*     (lua_topointer)(lua_State* L, int idx);\n";
	char options[] = "align-pointer=type, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException& ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int * value,\n"
		"                   int & num,\n"
		"                   std::vector<int> * a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int* value,\n"
		"                   int& num,\n"
		"                   std::vector<int>* a\n"
		"                   std::vector<int>& b)\n"
		"{}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*>* tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, AndOperator1)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, AndOperator2)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    ac >= 0 && ac < buflen - 1 ? next = buf.GetChar;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    x=a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, Sans3)
{
	// data on the next line is not a pointer
	char text[] =
		"\nDuration duration = new Duration(\n"
		"    new TimeSpan(TimeSpan.TicksPerMillisecond *\n"
		"                 100));";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, CppCLI)
{
	// test align-pointer=type on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int>^ intArr;\n"
		"    List<double>^ doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object^    o1 = s1;\n"
		"    Object^  o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int* pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, CSharp)
{
	// test align-pointer=type on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int * eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=type, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, RvalueReference)
{
	// test align-pointer=type on an rvalue reference.
	char textIn[] =
		"\nMemoryBlock &&f(MemoryBlock &&block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock&& f(MemoryBlock&& block)\n"
		"{\n"
		"    A&& a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T&& t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, RvalueReferenceDeclaration1)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int&&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo3( int && );\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int&&);\n"
		"    void Foo2(int&&);\n"
		"    void Foo3( int&& );\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, RvalueReferenceDeclaration2)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct A {\n"
		"    A & operator=( const A && );\n"
		"};";
	char text[] =
		"\nstruct A {\n"
		"    A& operator=( const A&& );\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, RvalueReferenceOperatorOverload)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test && rhs);\n"
		"};";
	char text[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test&& rhs);\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, ClosingFollowingChar)
{
	// Following a * is not closed for templates.
	char textIn[] =
		"\n"
		"void Foo( char*, char * );     // comment\n"
		"void Foo(char *, char*);       // comment\n"
		"\n"
		"vector< ParseTree * > m_TreeStack;   // comment\n"
		"vector<ParseTree*> m_TreeStack;      // comment\n";
	char text[] =
		"\n"
		"void Foo( char*, char* );      // comment\n"
		"void Foo(char*, char*);        // comment\n"
		"\n"
		"vector< ParseTree* > m_TreeStack;    // comment\n"
		"vector<ParseTree*> m_TreeStack;      // comment\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, TrailingReferenceType)
{
	// Using a trailing reference type in a function declaration.
	// Should not change the alignment.
	char text[] =
		"\n"
		"auto method(int x)->int&;\n"
		"auto method(int x)->int &;\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerType, SquareBrackets)
{
	// A * in brackets is an operator.
	// Should not change the alignment.
	char text[] =
		"\nclass Matrix\n"
		"{\n"
		"    Matrix() : data(new ValueType[m * n]) {}\n"
		"};";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer Middle
//-------------------------------------------------------------------------

TEST(AlignPointerMiddle, LongOption)
{
	// test align pointer=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string * bar;    // comment\n"
		"    const string * bar;    // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string * bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ShortOption)
{
	// test align pointer=middle short option
	char textIn[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string *bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)\n"
		"{\n"
		"    const string * bar;\n"
		"    const string * bar;\n"
		"}\n";
	char options[] = "-k2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	* bar;\n"
		"    const char	*	bar;\n"
		"    const char	*	bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Dereference)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char **)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int ** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Dereference3)
{
	// a dereference following a cast should not be space padded
	char text[] =
		"\nvoid Foo();\n"
		"{\n"
		"    wxImageHandler * handler = (wxImageHandler *)\n"
		"                               *node;\n"
		"}";
	char options[] = "align-pointer=middle, pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream * _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream * _err = NULL;\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void *foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void * foo(char * fooBar);\n"
		"char & bar(char &);\n";;
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Cast1)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;         // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Cast2)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void*fooBar, void* fooBar);\n";
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void * fooBar, void * fooBar);\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*	channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void*			userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox * channel;\n"
		"    wxTextCtrl * filename;\n"
		"    char      *     stamp;\n"
		"    void      *     userData;\n"
		"}\n";
	char options[] = "align-pointer=middle, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PointerToPointer1)
{
	// test pointer to pointer
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char ** argv)\n"
		"{\n"
		"    char  **  bar1;\n"
		"    char  **  bar1;\n"
		"    char  **  bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char ** bar1;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PointerToPointer2)
{
	// test pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PointerToPointer3)
{
	// test pointer to pointer with space separation
	// these do not change because of a multiply then a dereference (a * *b)
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    * *bar1;\n"
		"    char  * *  bar1;\n"
		"    char* *    bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char ** argv)\n"
		"{\n"
		"    char    * *bar1;\n"
		"    char  * *  bar1;\n"
		"    char* *    bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void *     // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char **\n"
		"bar() {}\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, EndOfLine3)
{
	// test reference at end of line
	char text[] =
		"\nwxPdfColour &\n"
		"wxPdfColour::operator= ( const wxPdfColour &\n"
		"                         colour )\n"
		"{}";
	char options[] = "align-pointer=middle, pad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, EndOfLine4)
{
	// test pointer at end of line with extra spacing
	// the extra spacing should not change or it will cause formatting on subsequent runs
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    char*\n"
		"    foo1;\n"
		"\n"
		"    char *\n"
		"    foo2;\n"
		"\n"
		"    char   *\n"
		"    foo3;\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    char *\n"
		"    foo1;\n"
		"\n"
		"    char *\n"
		"    foo2;\n"
		"\n"
		"    char   *\n"
		"    foo3;\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, BeginLine1)
{
	// a pointer begins the line
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    ** Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    * Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, BeginLine2)
{
	// a pointer begins the line and is followed by a comment
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;      //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;       //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    ** Names1;     //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    * Names4;      //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Comment1)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList * /*keyword*/,\n"
		"         WordList ** /*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Comment2)
{
	// test pointer with comment after and a default variable
	char textIn[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu* /*menu*/,\n"
		"                     const FileTreeData* /*data*/ = 0)\n"
		"{}";
	char text[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu * /*menu*/,\n"
		"                     const FileTreeData * /*data*/ = 0)\n"
		"{}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, BeforeEqual)
{
	// don't convert '& =' to '&='
	char textIn[] =
		"\nvoid SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString  &  = _(\",\"));\n";
	char text[] =
		"\nvoid SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString  &  = _(\",\"));\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T & operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef & () { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef & ();\n"
		"operator HIRect * ();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef & rf = (EventRef &) tf;\n"
		"HIRect * pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ScopeResolution1)
{
	// should not pad a scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::*  var;\n"
		"} cv;\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ScopeResolution2)
{
	// should not pad a scope resolution operator
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"public:\n"
		"    template<typename C, typename T> operator T C::*\n"
		"    () const {\n"
		"        return (T C::*)0;\n"
		"    }\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, FunctionPointer)
{
	// test char* in a function pointer
	char textIn[] =
		"\nvoid STDCALL Foo(char* (STDCALL *fpAlloc)(unsigned long));";
	char text[] =
		"\nvoid STDCALL Foo(char * (STDCALL * fpAlloc)(unsigned long));";
	char options[] = "align-pointer=middle, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PadParenOutside)
{
	// should not change scope resolution operator
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR) & showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) & maxText},\n"
		"        { IconID,   (LPTSTR) & iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=middle, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut1;
	delete[] textOut;
}

TEST(AlignPointerMiddle, PadParenEmpty)
{
	// an empty pad paren should align in the middle
	char textIn[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T* () const {\n"
		"        return (T*) 0;\n"
		"    }\n"
		"};";
	char text[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T * () const {\n"
		"        return (T *) 0;\n"
		"    }\n"
		"};";
	char options[] = "align-pointer=middle, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State   *  (lua_tothread)(lua_State * L, int idx);\n"
		"LUA_API const void   *  (lua_topointer)(lua_State * L, int idx);\n";
	char options[] = "align-pointer=middle, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException & ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int* value,\n"
		"                   int &num,\n"
		"                   std::vector<int> *a\n"
		"                   std::vector<int>& b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int * value,\n"
		"                   int & num,\n"
		"                   std::vector<int> * a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string *> * tempStack1;\n"
		"    vector<string *> * tempStack1;\n"
		"    vector<string *> * tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, AndOperator1)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, AndOperator2)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    ac >= 0 && ac < buflen - 1 ? next = buf.GetChar;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    x=a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=middle, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, CppCLI)
{
	// test align-pointer=middle on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^ doubleList;\n"
		"    String ^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object ^ o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^ str, int * pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, CSharp)
{
	// test align-pointer=middle on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int *eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int * eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=middle, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, RvalueReference)
{
	// test align-pointer=middle on an rvalue reference.
	char textIn[] =
		"\nMemoryBlock &&f(MemoryBlock&& block)\n"
		"{\n"
		"    A &&a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T&& t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock && f(MemoryBlock && block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B && a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T &&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, RvalueReferenceDeclaration1)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int&&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo3( int && );\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int &&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo3( int && );\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, RvalueReferenceDeclaration2)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct A {\n"
		"    A& operator=( const A&& );\n"
		"};";
	char text[] =
		"\nstruct A {\n"
		"    A & operator=( const A && );\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, RvalueReferenceOperatorOverload)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test&&rhs);\n"
		"};";
	char text[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test && rhs);\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, ClosingFollowingChar)
{
	// Following a * is not closed for templates.
	char textIn[] =
		"\n"
		"void Foo( char*, char * );     // comment\n"
		"void Foo(char *, char*);       // comment\n"
		"\n"
		"vector< ParseTree * > m_TreeStack;   // comment\n"
		"vector<ParseTree*> m_TreeStack;      // comment\n";
	char text[] =
		"\n"
		"void Foo( char *, char * );    // comment\n"
		"void Foo(char *, char *);      // comment\n"
		"\n"
		"vector< ParseTree * > m_TreeStack;   // comment\n"
		"vector<ParseTree *> m_TreeStack;     // comment\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, TrailingReferenceType)
{
	// Using a trailing reference type in a function declaration.
	// Should not change the alignment.
	char text[] =
		"\n"
		"auto method(int x)->int&;\n"
		"auto method(int x)->int &;\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerMiddle, SquareBrackets)
{
	// A * in brackets is an operator.
	// Should not change the alignment.
	char text[] =
		"\nclass Matrix\n"
		"{\n"
		"    Matrix() : data(new ValueType[m*n]) {}\n"
		"};";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer Name
//-------------------------------------------------------------------------

TEST(AlignPointerName, LongOption)
{
	// test align pointer=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string *bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string *bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ShortOption)
{
	// test align pointer=name short option
	char textIn[] =
		"\nstring foo(const string* bar)\n"
		"{\n"
		"    const string *bar;\n"
		"    const string* bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string *bar;\n"
		"    const string *bar;\n"
		"}\n";
	char options[] = "-k3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, FromCentered)
{
	// test align pointer=name when input is centered
	// a space is deleted in certain circumstances
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;     // remove space\n"
		"    const string  * bar;    // don't remove\n"
		"    const string *  bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string ** bar;    // remove space\n"
		"    const string  ** bar;   // don't remove\n"
		"    const string **  bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string & bar;     // remove space\n"
		"    const string  & bar;    // don't remove\n"
		"    const string &  bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;      // remove space\n"
		"    const string   *bar;    // don't remove\n"
		"    const string   *bar;    // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string **bar;     // remove space\n"
		"    const string   **bar;   // don't remove\n"
		"    const string   **bar;   // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string &bar;      // remove space\n"
		"    const string   &bar;    // don't remove\n"
		"    const string   &bar;    // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char*	bar;\n"
		"    const char	*	bar;\n"
		"    const char		*bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char		*bar;\n"
		"    const char				*bar;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Dereference)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char **)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int **pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Dereference3)
{
	// a dereference following a cast should not be space padded
	char text[] =
		"\nvoid Foo();\n"
		"{\n"
		"    wxImageHandler *handler = (wxImageHandler *)\n"
		"                              *node;\n"
		"}";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream *_err = &cerr;\n"
		"ASConsole *g_console;\n"
		"stringstream *_err = NULL;\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void* foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void *foo(char *fooBar);\n"
		"char &bar(char &);\n";;
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Cast1)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Cast2)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void*fooBar, void* fooBar);\n";
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void *fooBar);\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*	channel;\n"
		"    wxTextCtrl*	filename;\n"
		"    char		*	stamp;\n"
		"    void*			userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox  *channel;\n"
		"    wxTextCtrl *filename;\n"
		"    char           *stamp;\n"
		"    void           *userData;\n"
		"}\n";
	char options[] = "align-pointer=name, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PointerToPointer1)
{
	// test pointer to pointer
	char textIn[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char**    bar1;\n"
		"    char  **  bar1;\n"
		"    char    **bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char    **bar1;\n"
		"    char    **bar1;\n"
		"    char		**bar1;\n"
		"    char				**bar1;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PointerToPointer2)
{
	// test pointer to pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             **chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PointerToPointer3)
{
	// test pointer to pointer with space separation
	// these do not change because of a multiply then a dereference (a * *b)
	char textIn[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char* *    bar1;\n"
		"    char  * *  bar1;\n"
		"    char    * *bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char* *    bar1;\n"
		"    char  * *  bar1;\n"
		"    char    * *bar1;\n"
		"    char	*	*	bar1;\n"
		"    char		*	*		bar1;\n"
		"    char* *bar1;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void *     // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char **\n"
		"bar() {}\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, EndOfLine3)
{
	// test reference at end of line
	char text[] =
		"\nwxPdfColour &\n"
		"wxPdfColour::operator= ( const wxPdfColour &\n"
		"                         colour )\n"
		"{}";
	char options[] = "align-pointer=name, pad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, BeginLine1)
{
	// a pointer begins the line
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;\n"
		"    const wxChar\n"
		"    ** Names2;\n"
		"    const wxChar\n"
		"    **   Names3;\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;\n"
		"    const wxChar\n"
		"    * Names5;\n"
		"    const wxChar\n"
		"    *   Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;\n"
		"    const wxChar\n"
		"    ^   Names8;\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;\n"
		"    const wxChar\n"
		"    **Names2;\n"
		"    const wxChar\n"
		"    **Names3;\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;\n"
		"    const wxChar\n"
		"    *Names5;\n"
		"    const wxChar\n"
		"    *Names6;\n"
		"\n"
		"    const wxChar\n"
		"    &Names7;\n"
		"    const wxChar\n"
		"    ^Names8;\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, BeginLine2)
{
	// a pointer begins the line and is followed by a comment
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;      //!< An array of names\n"
		"    const wxChar\n"
		"    ** Names2;     //!< An array of names\n"
		"    const wxChar\n"
		"    **   Names3;   //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;       //!< An array of names\n"
		"    const wxChar\n"
		"    * Names5;      //!< An array of names\n"
		"    const wxChar\n"
		"    *   Names6;    //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &   Names7;    //!< An array of names\n"
		"    const wxChar\n"
		"    ^   Names8;    //!< An array of names\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    const wxChar\n"
		"    **Names1;      //!< An array of names\n"
		"    const wxChar\n"
		"    **Names2;      //!< An array of names\n"
		"    const wxChar\n"
		"    **Names3;      //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    *Names4;       //!< An array of names\n"
		"    const wxChar\n"
		"    *Names5;       //!< An array of names\n"
		"    const wxChar\n"
		"    *Names6;       //!< An array of names\n"
		"\n"
		"    const wxChar\n"
		"    &Names7;       //!< An array of names\n"
		"    const wxChar\n"
		"    ^Names8;       //!< An array of names\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Comment1)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList */*keyword*/,\n"
		"         WordList **/*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Comment2)
{
	// test pointer with comment after and a default variable
	char textIn[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu* /*menu*/,\n"
		"                     const FileTreeData * /*data*/ = 0)\n"
		"{}";
	char text[] =
		"\nvoid BuildModuleMenu(const ModuleType /*type*/,\n"
		"                     wxMenu * /*menu*/,\n"
		"                     const FileTreeData * /*data*/ = 0)\n"
		"{}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, BeforeEqual)
{
	// don't convert '& =' to '&='
	char textIn[] =
		"\nvoid SetMasks1(const wxString& = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString  &  = _(\",\"));\n";
	char text[] =
		"\nvoid SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString & = _(\",\"));\n"
		"void SetMasks1(const wxString   & = _(\",\"));\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T &operator* () const {};\n"
		"    T *operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect *() { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef &();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef &rf = (EventRef &) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ScopeResolution1)
{
	// should not pad a scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"} cv;\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ScopeResolution2)
{
	// should not pad a scope resolution operator
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"public:\n"
		"    template<typename C, typename T> operator T C::*\n"
		"    () const {\n"
		"        return (T C::*)0;\n"
		"    }\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, FunctionPointer)
{
	// test char* in a function pointer
	char textIn[] =
		"\nvoid STDCALL Foo(char * (STDCALL * fpAlloc)(unsigned long));";
	char text[] =
		"\nvoid STDCALL Foo(char *(STDCALL *fpAlloc)(unsigned long));";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PadParenOutside)
{
	// test align-pointer with pad-paren-out
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR) &showIcon},\n"
		"        { Dynamic,  (LPTSTR) &isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR) &iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=name, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut1;
	delete[] textOut;
}

TEST(AlignPointerName, PadParenEmpty)
{
	// an empty pad paren should not pad a pointer
	char textIn[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T* () const {\n"
		"        return (T*) 0;\n"
		"    }\n"
		"};";
	char text[] =
		"\nconst class nullptr_t\n"
		"{\n"
		"public:\n"
		"    template<typename T> operator T *() const {\n"
		"        return (T *) 0;\n"
		"    }\n"
		"};";
	char options[] = "align-pointer=name, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void*     (lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char options[] = "align-pointer=name, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException &ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int * value,\n"
		"                   int& num,\n"
		"                   std::vector<int>* a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int *value,\n"
		"                   int &num,\n"
		"                   std::vector<int> *a\n"
		"                   std::vector<int> &b)\n"
		"{}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string *> *tempStack1;\n"
		"    vector<string *> *tempStack1;\n"
		"    vector<string *> *tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, AndOperator1)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, AndOperator2)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    ac >= 0 && ac < buflen - 1 ? next = buf.GetChar;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    x=a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    x = a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, CppCLI)
{
	// test align-pointer=name on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^ doubleList;\n"
		"    String ^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object ^ o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^ str, int * pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^stringVar;\n"
		"    array<int> ^intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String ^s1 = \"abc\";\n"
		"    Object    ^o1 = s1;\n"
		"    Object ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, CSharp)
{
	// test align-pointer=type on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int *j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int *eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=name, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, RvalueReference)
{
	// test align-pointer=name on an rvalue reference.
	char textIn[] =
		"\nMemoryBlock&& f(MemoryBlock&& block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock &&f(MemoryBlock &&block)\n"
		"{\n"
		"    A &&a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T &&t)\n"
		"{\n"
		"    S<T &&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, RvalueReferenceDeclaration1)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int&&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo3( int && );\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    void Foo1(int &&);\n"
		"    void Foo2(int &&);\n"
		"    void Foo3( int && );\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, RvalueReferenceDeclaration2)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct A {\n"
		"    A& operator=( const A&& );\n"
		"};";
	char text[] =
		"\nstruct A {\n"
		"    A &operator=( const A && );\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, RvalueReferenceOperatorOverload)
{
	// test on a rvalue reference in a declaration.
	char textIn[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test && rhs);\n"
		"};";
	char text[] =
		"\nstruct Test\n"
		"{\n"
		"    Test operator=(Test &&rhs);\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, ClosingFollowingChar)
{
	// Following a * is not closed for templates.
	char textIn[] =
		"\n"
		"void Foo( char*, char * );     // comment\n"
		"void Foo(char *, char*);       // comment\n"
		"\n"
		"vector< ParseTree * > m_TreeStack;   // comment\n"
		"vector<ParseTree*> m_TreeStack;      // comment\n";
	char text[] =
		"\n"
		"void Foo( char *, char * );    // comment\n"
		"void Foo(char *, char *);      // comment\n"
		"\n"
		"vector< ParseTree * > m_TreeStack;   // comment\n"
		"vector<ParseTree *> m_TreeStack;     // comment\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, TrailingReferenceType)
{
	// Using a trailing reference type in a function declaration.
	// Should not change the alignment.
	char text[] =
		"\n"
		"auto method(int x)->int&;\n"
		"auto method(int x)->int &;\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignPointerName, SquareBrackets)
{
	// A * in brackets is an operator.
	// Should not change the alignment.
	char text[] =
		"\nclass Matrix\n"
		"{\n"
		"    Matrix() : data(new ValueType[m * n]) {}\n"
		"};";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer Other
//-------------------------------------------------------------------------

TEST(AlignPointer, ShortLowerLimit)
{
	// test error handling for the short option lower limit
	// should call the error handler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	// use errorHandler2 to verify the error
	char options[] = "-k0";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete[] textOut;
}

TEST(AlignPointer, ShortUpperLimit)
{
	// test error handling for the short option upper limit
	// should call the error handler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	// use errorHandler2 to verify the error
	char options[] = "-k4";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete[] textOut;
}

TEST(AlignPointer, Java)
{
	// align-pointer should have no effect on Java
	// should pad-oper not align-pointer=type
	char textIn[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length*count);\n"
		"    return (modifier&query) == query;\n"
		"}\n";
	char text[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length * count);\n"
		"    return (modifier & query) == query;\n"
		"}\n";
	char options[] = "mode=java, pad-oper, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Reference
// Align Reference is tested with Align Pointer
//-------------------------------------------------------------------------

TEST(AlignReferenceNone, ShortOption)
{
	// test align-reference=none short option
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "-W0";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceNone, PointerNone)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceNone, PointerType)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceNone, PointerMiddle)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string * bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceNone, PointerName)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceNone, PointerName_Rvalue)
{
	// Rvalue references should not be changed.
	char text[] =
		"\nMemoryBlock&& f(MemoryBlock &&block)\n"
		"{\n"
		"    A&& a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-reference=none, align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, ShortOption)
{
	// test align-reference=type short option
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "-W1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, PointerNone)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, PointerType)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, PointerMiddle)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, PointerName)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceType, PointerName_Rvalue)
{
	// test align-reference=type with rvalue reference
	char textIn[] =
		"\nMemoryBlock &&f(MemoryBlock &&block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock&& f(MemoryBlock&& block)\n"
		"{\n"
		"    A&& a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T&& t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-reference=type, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, ShortOption)
{
	// test align-reference=middle short option
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "-W2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, PointerNone)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, PointerType)
{
	// test align-reference=middle with rvalue reference
	char textIn[] =
		"\nMemoryBlock &&f(MemoryBlock&& block)\n"
		"{\n"
		"    A &&a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T&& t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock && f(MemoryBlock && block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B && a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T &&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-reference=middle, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, PointerMiddle)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, PointerName)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceMiddle, PointerName_Rvalue)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, ShortOption)
{
	// test align-reference=name short option
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "-W3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, PointerNone)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, PointerType)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, PointerMiddle)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, Pointername)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceName, PointerType_Rvalue)
{
	// test align-reference=name with rvalue reference
	char textIn[] =
		"\nMemoryBlock&& f(MemoryBlock&& block)\n"
		"{\n"
		"    A && a_ref2 = a;\n"
		"    B&& a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T && t)\n"
		"{\n"
		"    S<T&&>::print(std::forward<T>(t));\n"
		"}";
	char text[] =
		"\nMemoryBlock &&f(MemoryBlock &&block)\n"
		"{\n"
		"    A &&a_ref2 = a;\n"
		"    B &&a_ref4 = B();\n"
		"    return block;\n"
		"}\n"
		"\n"
		"template <typename T>\n"
		"void print_type_and_value(T &&t)\n"
		"{\n"
		"    S<T &&>::print(std::forward<T>(t));\n"
		"}";
	char options[] = "align-reference=name, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer and Align Reference for special case of Reference to a Pointer (*&)
// Cannot have a Pointer to a Reference (&*)
//-------------------------------------------------------------------------

TEST(AlignReferenceToPointer, PointerType_ReferenceDefault)
{
	// Test *& with align-pointer=type and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>*& container)\n"
		"{}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceType)
{
	// Test *& with align-pointer=type and align-reference=type.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>*& container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceMiddle)
{
	// Test *& with align-pointer=type and align-reference=middle.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>* & container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* & container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceName)
{
	// Test *& with align-pointer=type and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>* &container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* &container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerType_CommentFollows)
{
	// Test *& with align-pointer=type and a following comment.
	char textIn[] =
		"\n"
		"void Method1(char*& data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char *& data,    // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char *&data,     // Data\n"
		"             int length);     // Length\n";
	char text[] =
		"\n"
		"void Method1(char*& data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char*& data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char*& data,     // Data\n"
		"             int length);     // Length\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceType_)
{
	// Test *& with align-pointer=middle and align-reference=type.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceDefault)
{
	// Test *& with align-pointer=middle and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> *& container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceMiddle)
{
	// Test *& with align-pointer=middle and align-reference=middle.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> *& container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceName)
{
	// Test *& with align-pointer=middle and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> * &container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * &container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_CommentFollows)
{
	// Test *& with align-pointer=middle and a following comment.
	char textIn[] =
		"\n"
		"void Method1(char*& data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char *& data,    // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char *&data,     // Data\n"
		"             int length);     // Length\n";
	char text[] =
		"\n"
		"void Method1(char *& data,    // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char *& data,    // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char *& data,    // Data\n"
		"             int length);     // Length\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceType)
{
	// Test *& with align-pointer=name and align-reference=type.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceMiddle)
{
	// Test *& with align-pointer=name and align-reference=middle.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceDefault)
{
	// Test *& with align-pointer=middle and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceName)
{
	// Test *& with align-pointer=name and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignReferenceToPointer, PointerName_CommentFollows)
{
	// Test *& with align-pointer=name and a following comment.
	char textIn[] =
		"\n"
		"void Method1(char*& data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char *& data,    // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char *&data,     // Data\n"
		"             int length);     // Length\n";
	char text[] =
		"\n"
		"void Method1(char *&data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method2(char *&data,     // Data\n"
		"             int length);     // Length\n"
		"\n"
		"void Method3(char *&data,     // Data\n"
		"             int length);     // Length\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
