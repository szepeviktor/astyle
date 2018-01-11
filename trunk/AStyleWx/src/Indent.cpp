// Indent.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleWx.h"

#ifdef __BORLANDC__
	#pragma warn -8004	// variable is assigned a value that is never used
#endif

// -----------------------------------------------------------------------------
// constants
// -----------------------------------------------------------------------------

/// Codes representing the effect a line has on indentation.
enum IndentationStatus
{
	isNone,			// no effect on indentation
	isBlockStart,	// indentation block begin such as "{"
	isBlockEnd,		// indentation end indicator such as "}"
	isKeyWordStart	// Keywords that cause indentation
};

std::string statementIndent("case default do else for if while");
std::string statementEnd(";");
std::string blockStart("{");
std::string blockEnd("}");

int  statementLookback = 10;

// should be options
bool indentOpening = false;
bool indentClosing = false;

//-----------------------------------------------------------------------------
// ASEditor class
//-----------------------------------------------------------------------------

void ASEditor::AutomaticIndentation(int ch)
{
	int curPos = wxStyledTextCtrl::GetCurrentPos();
	int curLine = wxStyledTextCtrl::LineFromPosition(curPos);
	int thisLineStart = wxStyledTextCtrl::PositionFromLine(curLine);
	int indentSize = GetIndentSize();
	int indentBlock = IndentOfBlock(curLine - 1);

	if (ch == '}')
	{
		// Dedent maybe
		if (!indentClosing)
		{
			if (RangeIsAllWhitespace(thisLineStart, curPos - 1))
			{
				SetLineIndentation(curLine, indentBlock - indentSize);
				int indentPos = GetLineIndentPosition(curLine);
				wxStyledTextCtrl::GotoPos(indentPos + 1);
			}
		}
	}
	else if (ch == '{')
	{
		// Dedent maybe if first on line and previous line was starting keyword
		if (!indentOpening && (GetIndentState(curLine - 1) == isKeyWordStart))
		{
			if (RangeIsAllWhitespace(thisLineStart, curPos - 1))
			{
				SetLineIndentation(curLine, indentBlock - indentSize);
				int indentPos = GetLineIndentPosition(curLine);
				wxStyledTextCtrl::GotoPos(indentPos + 1);
			}
		}
	}
	else if ((ch == '\r' || ch == '\n') && (curPos == thisLineStart))
	{
		SetLineIndentation(curLine, indentBlock);
	}
}

int ASEditor::GetIndentSize()
{
	// If the indentSize is 0, the indent size is the same as the tab size.
	int indentSize = wxStyledTextCtrl::GetIndent();
	if (indentSize == 0)
		indentSize = wxStyledTextCtrl::GetTabWidth();
	return indentSize;
}

int ASEditor::GetIndentState(int line)
{
	// C like language indentation defined by braces and keywords
	IndentationStatus indentState = isNone;
	// Get keywords.
	std::string controlWords[20];
	int controlWordsLen = sizeof(controlWords) / sizeof(controlWords[0]);
	size_t parts = GetLinePartsInStyle(line, wxSTC_C_WORD, -1,
	                                   controlWords, controlWordsLen);
	for (size_t i = 0; i < parts; i++)
	{
		if (Includes(statementIndent, controlWords[i]))
			indentState = isKeyWordStart;
	}
	// Semicolons override keywords.
	std::string controlStrings[20];
	int controlStringsLen = sizeof(controlStrings) / sizeof(controlStrings[0]);
	parts = GetLinePartsInStyle(line, wxSTC_C_OPERATOR, -1,
	                            controlStrings, controlStringsLen);
	for (size_t i = 0; i < parts; i++)
	{
		if (Includes(statementEnd, controlStrings[i]))
			indentState = isNone;
	}
	// Braces override semicolons and keywords.
	for (size_t j = 0; j < parts; j++)
	{
		if (Includes(blockEnd, controlStrings[j]))
			indentState = isBlockEnd;
		if (Includes(blockStart, controlStrings[j]))
			indentState = isBlockStart;
	}
	return indentState;
}

int ASEditor::GetLinePartsInStyle(int line, int style1, int style2, std::string sv[], int len)
{
	for (int i = 0; i < len; i++)
		sv[i].erase();
	std::string s;
	int part = 0;
	int thisLineStart = wxStyledTextCtrl::PositionFromLine(line);
	int nextLineStart = wxStyledTextCtrl::PositionFromLine(line + 1);
	for (int pos = thisLineStart; pos < nextLineStart; pos++)
	{
		if ((wxStyledTextCtrl::GetStyleAt(pos) == style1)
		        || (wxStyledTextCtrl::GetStyleAt(pos) == style2))
		{
			char c[2];
			c[0] = static_cast<wxChar>(wxStyledTextCtrl::GetCharAt(pos));
			c[1] = '\0';
			s += c;
		}
		else if (s.length() > 0)
		{
			if (part < len)
				sv[part++] = s;
			s.erase();
		}
	}
	if ((s.length() > 0) && (part < len))
		sv[part++] = s;
	return part;
}

bool ASEditor::Includes(const std::string& symbols, const std::string& value)
{
	if (symbols.length() == 0)
		return false;

	if (isalpha(symbols[0]))
	{
		// Set of symbols separated by spaces
		size_t start = 0;
		size_t end = 0;
		while (start < symbols.length())
		{
			end = symbols.find(' ', start);
			if (end == std::string::npos)
				end = symbols.length();
			std::string word = symbols.substr(start, end - start);
			if (word == value)
				return true;
			start = ++end;
		}
	}
	else
	{
		// Set of individual characters. Only one character allowed for now
		char ch = symbols[0];
		return strchr(value.c_str(), ch) != 0;
	}
	return false;
}

int ASEditor::IndentOfBlock(int line)
{
	if (line < 0)
		return 0;
	int indentSize = GetIndentSize();
	int indentBlock = wxStyledTextCtrl::GetLineIndentation(line);
	int backLine = line;
	IndentationStatus indentState = isNone;

	int lineLimit = line - statementLookback;
	if (lineLimit < 0)
		lineLimit = 0;
	while ((backLine >= lineLimit) && (indentState == 0))
	{
		indentState = static_cast<IndentationStatus>(GetIndentState(backLine));
		if (indentState != 0)
		{
			indentBlock = wxStyledTextCtrl::GetLineIndentation(backLine);
			if (indentState == isBlockStart)
			{
				if (!indentOpening)
					indentBlock += indentSize;
			}
			if (indentState == isBlockEnd)
			{
				if (indentClosing)
					indentBlock -= indentSize;
				if (indentBlock < 0)
					indentBlock = 0;
			}
			if ((indentState == isKeyWordStart) && (backLine == line))
				indentBlock += indentSize;
		}
		backLine--;
	}
	return indentBlock;
}

bool ASEditor::RangeIsAllWhitespace(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if ((wxStyledTextCtrl::GetCharAt(i) != ' ')
		        && (wxStyledTextCtrl::GetCharAt(i) != '\t')
		        && (wxStyledTextCtrl::GetStyleAt(i) != wxSTC_C_DEFAULT))
			return false;
	}
	return true;
}

void ASEditor::SetLineIndentation(int line, int indent)
{
	if (indent < 0)
		return;
	wxStyledTextCtrl::SetLineIndentation(line, indent);
	int indentPos = GetLineIndentPosition(line);
	wxStyledTextCtrl::GotoPos(indentPos);
}
