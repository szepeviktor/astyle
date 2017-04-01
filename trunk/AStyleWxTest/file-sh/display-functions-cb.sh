#!/lib/bash
# display the entry functions for astyle shared libraries in the codeblocks build files
# Exported symbols are indicated by a T

astylewx=$HOME/Projects/AStyleWx/build
sonamevar=3.0

cd  $astylewx

echo clang
nm -D --defined-only cb-clang/lib/libastyle.so.$sonamevar   | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-clang/lib/libastyled.so.$sonamevar  | grep ' T ' | head -20 | cut -c -70

echo
echo gcc
nm -D --defined-only cb-gcc/lib/libastyle.so.$sonamevar      | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-gcc/lib/libastyled.so.$sonamevar     | grep ' T ' | head -20 | cut -c -70

echo
echo intel
# intel release has extra functions at the start
nm -D --defined-only cb-intel/lib/libastyle.so.$sonamevar    | grep ' T ' | head -43 | cut -c -70
echo
nm -D --defined-only cb-intel/lib/libastyled.so.$sonamevar   | grep ' T ' | head -20 | cut -c -70


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
