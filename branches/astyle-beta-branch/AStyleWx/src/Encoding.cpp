// Encoding.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "Encoding.h"

#include <wx/encconv.h>
#include <wx/file.h>
#include <wx/fontmap.h>
#include <wx/intl.h>
#include <wx/strconv.h>

#ifdef __BORLANDC__
	#pragma warn -8004	// variable is assigned a value that is never used
#endif

//-----------------------------------------------------------------------------
// Encoding class
//-----------------------------------------------------------------------------

Encoding::Encoding(const wxString& filename)
	: m_isOK(false),
	  m_usesBOM(false),
	  m_encoding(wxFONTENCODING_DEFAULT)
{
	m_isOK = DetectEncoding(filename);
}

bool Encoding::IsOK() const
{
	return m_isOK;
}

bool Encoding::UsesBOM() const
{
	return m_usesBOM;
}

wxFontEncoding Encoding::GetFileEncoding() const
{
	return m_encoding;
}

wxString& Encoding::GetConvertedText()
{
	return m_convertedText;
}

bool Encoding::DetectEncoding(const wxString& filename)
// Detect the file encoding and convert to a wide character (Unicode) string.
// Return true if success.
{
	wxFile file(filename);
	if (!file.IsOpened())
		return false;

	size_t size = file.Length();
	wxByte* buffer = new wxByte[sizeof(wxByte) * (size + 4)];
	if (!buffer)
	{
		file.Close();
		return false;
	}
	// null terminate the buffer
	buffer[size + 0] = 0;
	buffer[size + 1] = 0;
	buffer[size + 2] = 0;
	buffer[size + 3] = 0;

	size_t readBytes = file.Read(static_cast<void*>(buffer), size);
	assert(readBytes == size);

	if (readBytes == 0)
	{
		m_encoding = wxLocale::GetSystemEncoding();
		return true;
	}

	// detect UTF encodings with a BOM
	bool isConverted = DetectEncodingBOM(buffer, size);
	// use 8-bit encoding
	if (!isConverted && !m_usesBOM)
		isConverted = DetectEncoding8Bit(buffer, size);

	file.Close();
	delete[] buffer;
	return isConverted;
}

bool Encoding::DetectEncodingBOM(const wxByte* buffer, size_t size)
// Detect and convert encoding on files that have a Byte Order Mark (BOM).
{
	if (!buffer)
		return false;

	size_t outlen = 0;
	wxWCharBuffer wideBuff;

	// check for Byte Order Mark (BOM)

	// BOM is max 4 bytes
	size_t BOMSize = 0;
	char buff[4] = {'\0'};
	memcpy(buff, buffer, 4);

	// UTF8 (BOM)
	if (memcmp(buff, "\xEF\xBB\xBF", 3) == 0)
	{
		BOMSize = 3;
		m_usesBOM = true;
		m_encoding = wxFONTENCODING_UTF8;
		wxMBConvUTF8 conv;
		wideBuff = conv.cMB2WC((char*)buffer + BOMSize, size - BOMSize, &outlen);
	}
	// UTF32BE (BOM)
	else if (memcmp(buff, "\x00\x00\xFE\xFF", 4) == 0)
	{
		BOMSize = 4;
		m_usesBOM = true;
		m_encoding = wxFONTENCODING_UTF32BE;
		wxMBConvUTF32BE conv;
		wideBuff = conv.cMB2WC((char*)buffer + BOMSize, size - BOMSize, &outlen);
	}
	// UTF32LE (BOM)
	else if (memcmp(buff, "\xFF\xFE\x00\x00", 4) == 0)
	{
		BOMSize = 4;
		m_usesBOM = true;
		m_encoding = wxFONTENCODING_UTF32LE;
		wxMBConvUTF32LE conv;
		wideBuff = conv.cMB2WC((char*)buffer + BOMSize, size - BOMSize, &outlen);
	}
	// UTF16BE (BOM)
	else if (memcmp(buff, "\xFE\xFF", 2) == 0)
	{
		BOMSize = 2;
		m_usesBOM = true;
		m_encoding = wxFONTENCODING_UTF16BE;
		wxMBConvUTF16BE conv;
		wideBuff = conv.cMB2WC((char*)buffer + BOMSize, size - BOMSize, &outlen);
	}
	// UTF16LE (BOM)
	else if (memcmp(buff, "\xFF\xFE", 2) == 0)
	{
		BOMSize = 2;
		m_usesBOM = true;
		m_encoding = wxFONTENCODING_UTF16LE;
		wxMBConvUTF16LE conv;
		wideBuff = conv.cMB2WC((char*)buffer + BOMSize, size - BOMSize, &outlen);
	}
	// did not find a BOM
	else
		return false;

	assert(outlen < size);
	m_convertedText = wideBuff;
	return true;
}

bool Encoding::DetectEncoding8Bit(const wxByte* buffer, size_t size)
// Detect and convert 8-bit encoding.
{
	if (!buffer)
		return false;

	size_t outlen = 0;
	wxFontEncoding systemEncoding = wxLocale::GetSystemEncoding();
	wxWCharBuffer wideBuff;

	// Check file chars for non-ascii.
	// If yes, check for utf-8.
	// If not UTF-8 use system default.
	bool non_ascii = false;
	size_t sizeToCheck = size;
	if (sizeToCheck > 20000)	// about 800 lines
		sizeToCheck = 20000;
	for (size_t i = 0; i < sizeToCheck; i++)
	{
		if (buffer[i] > 128)
		{
			non_ascii = true;
			break;
		}
	}

	// If non-ascii chars check for UTF-8.
	if (non_ascii)
	{
		m_encoding = wxFONTENCODING_UTF8;
		wxMBConvUTF8 conv;
		wideBuff = conv.cMB2WC((char*)buffer, size, &outlen);
	}

	// If not UTF-8 use the system default.
	if (outlen == 0)
	{
		m_encoding = systemEncoding;
		wxCSConv convSystem(m_encoding);
		wideBuff = convSystem.cMB2WC((char*)buffer, size, &outlen);
	}

	// If not the system default use Windows-1252.
	if (outlen == 0 && systemEncoding != wxFONTENCODING_CP1252)
	{
		m_encoding = wxFONTENCODING_CP1252;
		wxCSConv convSystem(m_encoding);
		wideBuff = convSystem.cMB2WC((char*)buffer, size, &outlen);
	}

	if (outlen == 0)
		return false;

	// good conversion
	m_convertedText = wideBuff;

	return true;
}

//-----------------------------------------------------------------------------
// Static function to encode text
//-----------------------------------------------------------------------------

size_t Encoding::EncodeText(wxFontEncoding encoding, const wxString& textIn, wxCharBuffer& mbBuff)
{
	size_t outlen = 0;

	if (encoding == wxFONTENCODING_UTF8)
	{
		wxMBConvUTF8 conv;
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}
	else if (encoding == wxFONTENCODING_UTF32BE)
	{
		wxMBConvUTF32BE conv;
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}
	else if (encoding == wxFONTENCODING_UTF32LE)
	{
		wxMBConvUTF32LE conv;
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}
	else if (encoding == wxFONTENCODING_UTF16BE)
	{
		wxMBConvUTF16BE conv;
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}
	else if (encoding == wxFONTENCODING_UTF16LE)
	{
		wxMBConvUTF16LE conv;
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}
	else
	{
		wxCSConv conv(encoding);
		mbBuff = conv.cWC2MB(textIn.wc_str(), textIn.Len(), &outlen);
	}

	return outlen;
}
