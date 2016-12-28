#!/bin/bash
#  iconv- text encoding conversion

#  --from-code, -f encoding  Convert characters from encoding.
#  --to-code, -t encoding  Convert characters to encoding, or to current locale if not specified. 
#  --list, -l  List known coded character sets.
#  --verbose  Print progress information.
#  --help, -?  Give help list.

#  Example:  iconv -f ISO-8859-1 -t UTF-8 < input.txt > output.txt

# Windows code pages:
#      874  -- Thai
#      932  -- Japanese
#      936  -- Chinese (simplified) (PRC, Singapore)
#      949  -- Korean
#      950  -- Chinese (traditional) (Taiwan, Hong Kong)
#      1200 -- Unicode (BMP of ISO 10646, UTF-16LE)
#      1201 -- Unicode (BMP of ISO 10646, UTF-16BE)
#      1250 -- Latin (Central European languages)
#      1251 -- Cyrillic
#      1252 -- Latin (Western European languages)
#      1253 -- Greek
#      1254 -- Turkish
#      1255 -- Hebrew
#      1256 -- Arabic
#      1257 -- Latin (Baltic languages)
#      1258 -- Vietnamese
#      65000 -- Unicode (BMP of ISO 10646, UTF-7)
#      65001 -- Unicode (BMP of ISO 10646, UTF-8)

# ISO 8-bit character encodings:
#      ISO8859-1  -- West European (Latin1)
#      ISO8859-2  -- Central and East European (Latin2)
#      ISO8859-3  -- Esperanto (Latin3)
#      ISO8859-4  -- Baltic (old) (Latin4)
#      ISO8859-5  -- Cyrillic
#      ISO8859-6  -- Arabic
#      ISO8859-7  -- Greek
#      ISO8859-8  -- Hebrew
#      ISO8859-9  -- Turkish (Latin5)
#      ISO8859-10 -- Variation of Latin4 (Latin6)
#      ISO8859-11 -- Thai
#      ISO8859-12 -- doesn't exist currently
#      ISO8859-13 -- Baltic (Latin7)
#      ISO8859-14 -- Latin8
#      ISO8859-15 -- Latin9 (a.k.a. Latin0, includes euro)


indir=$HOME/Projects/AStyleWx/testdata
outdir=$HOME/Projects/AStyleWx/testi18n

# set these to select the charsets converted
unicode=no
windows=no
linux=yes

if [ ! -d  $outdir ]; then
	mkdir  --parents  $outdir
fi

if [ $unicode == "yes" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                         converting unicode                          *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	
	# Chinese Unicode ##########################################################
	echo copying Chinese-UTF8.txt
	iconv  -f  UTF16LE  -t  UTF-8  < $indir/Chinese.txt > $outdir/Chinese-UTF8.txt

	echo copying Chinese-UTF16BE.txt
	iconv  -f  UTF16LE  -t  UTF16BE  < $indir/Chinese.txt > $outdir/Chinese-UTF16BE.txt

	echo copying Chinese-UTF16LE.txt
	iconv  -f  UTF16LE  -t  UTF16LE  < $indir/Chinese.txt > $outdir/Chinese-UTF16LE.txt

	echo copying Chinese-UTF32BE.txt
	iconv  -f  UTF16LE  -t  UTF32BE  < $indir/Chinese.txt > $outdir/Chinese-UTF32BE.txt

	echo copying Chinese-UTF32LE.txt
	iconv  -f  UTF16LE  -t  UTF32LE  < $indir/Chinese.txt > $outdir/Chinese-UTF32LE.txt

	# German Unicode ###########################################################
	echo
	echo copying German-UTF8.txt
	iconv  -f  UTF16LE  -t  UTF-8  < $indir/German.txt > $outdir/German-UTF8.txt

	echo copying German-UTF16BE.txt
	iconv  -f  UTF16LE  -t  UTF16BE  < $indir/German.txt > $outdir/German-UTF16BE.txt

	echo copying German-UTF16LE.txt
	iconv  -f  UTF16LE  -t  UTF16LE  < $indir/German.txt > $outdir/German-UTF16LE.txt

	echo copying German-UTF32BE.txt
	iconv  -f  UTF16LE  -t  UTF32BE  < $indir/German.txt > $outdir/German-UTF32BE.txt

	echo copying German-UTF32LE.txt
	iconv  -f  UTF16LE  -t  UTF32LE  < $indir/German.txt > $outdir/German-UTF32LE.txt
fi

if [ $windows == "yes" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                         converting windows                          *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

	# This is the same as WINDOWS-936 and GB2312
	echo copying ChineseSimp-CP936.txt
	iconv  -f  UTF16LE  -t  CP936//TRANSLIT < $indir/Chinese.txt > $outdir/ChineseSimp-CP936.txt

	# This is the same as WINDOWS-1252
	# The same code page as English
	echo copying French-CP1252.txt
	iconv  -f  UTF16LE  -t  CP1252//TRANSLIT  < $indir/French.txt > $outdir/French-CP1252.txt

	# This is the same as WINDOWS-1252
	# The same code page as English
	echo copying German-CP1252.txt
	iconv  -f  UTF16LE  -t  CP1252//TRANSLIT   < $indir/German.txt > $outdir/German-CP1252.txt

	# This is the same as WINDOWS-932 and Shift_JIS
	echo copying Japanese-CP932.txt
	iconv  -f  UTF16LE  -t  CP932//TRANSLIT   < $indir/Japanese.txt > $outdir/Japanese-CP932.txt

	# This is the same as WINDOWS-949 and euc-kr
	echo copying Korean-CP949.txt
	iconv  -f  UTF16LE  -t  CP949//TRANSLIT   < $indir/Korean.txt > $outdir/Korean-CP949.txt

	# This is the same as WINDOWS-1251
	echo copying Russian-CP1251.txt
	iconv  -f  UTF16LE  -t   CP1251//TRANSLIT   < $indir/Russian.txt > $outdir/Russian-CP1251.txt
fi

if [ $linux == "yes" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                          converting linux                           *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

	# This is the same as WINDOWS-936 and GB2312
	echo copying ChineseSimp-GB2312.txt
	iconv  -f  UTF16LE  -t  GB2312//TRANSLIT < $indir/Chinese.txt > $outdir/ChineseSimp-GB2312.txt

	# This is the same as WINDOWS-1252
	# The same code page as English
	echo copying French-ISO8859-1.txt
	iconv  -f  UTF16LE  -t  ISO88591//TRANSLIT  < $indir/French.txt > $outdir/French-ISO8859-1.txt

	# This is the same as WINDOWS-1252
	# The same code page as English
	echo copying German-ISO8859-1.txt
	iconv  -f  UTF16LE  -t  ISO88591//TRANSLIT   < $indir/German.txt > $outdir/German-ISO8859-1.txt

	# This is the same as WINDOWS-932  and Shift_JIS
	echo copying Japanese-SHIFT-JIS.txt
	iconv  -f  UTF16LE  -t  SHIFT-JIS//TRANSLIT   < $indir/Japanese.txt > $outdir/Japanese-SHIFT-JIS.txt

	# This is the same as WINDOWS-949 and EUC-KR
	echo copying Korean-EUC-KR.txt
	iconv  -f  UTF16LE  -t  EUC-KR//TRANSLIT   < $indir/Korean.txt > $outdir/Korean-EUC-KR.txt

	echo copying Russian-ISO8859-5.txt
	iconv  -f  UTF16LE  -t   ISO88595//TRANSLIT   < $indir/Russian.txt > $outdir/Russian-ISO8859-5.txt
	
	echo copying Czech-ISO8859-2.txt
	iconv  -f  UTF16LE  -t   ISO88592//TRANSLIT   < $indir/Czech.txt > $outdir/Czech-ISO8859-2.txt
fi

echo
read -sn1 -p "Press any key to end . . ."
