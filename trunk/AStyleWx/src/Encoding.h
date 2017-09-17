//  Encoding.h
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef ENCODING_H
#define ENCODING_H

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/string.h>

//-----------------------------------------------------------------------------
// Encoding class
//-----------------------------------------------------------------------------

class Encoding
{
public:
	explicit Encoding(const wxString& filename);
	Encoding(const Encoding& rhs);
	~Encoding();

	static size_t EncodeText(wxFontEncoding encoding, const wxString& textIn, wxCharBuffer& mbBuff);
	wxFontEncoding GetFileEncoding() const;
	wxString& GetConvertedText();
	bool IsOK() const;
	bool UsesBOM() const;
private:
	bool m_isOK;
	bool m_usesBOM;
	wxFontEncoding m_encoding;
	wxString m_convertedText;
private:
	bool DetectEncoding(const wxString& filename);
	bool DetectEncodingBOM(const wxByte* buffer, size_t size);
	bool DetectEncoding8Bit(const wxByte* buffer, size_t size);
};

#endif // ENCODING_H
