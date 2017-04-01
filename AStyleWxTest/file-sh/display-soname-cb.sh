#!/lib/bash
# display the soname for astyle shared libraries in the codeblocks build files

astylewx=$HOME/Projects/AStyleWx/build
solibver=3.0

cd  $astylewx

echo cb-clang
objdump -p cb-clang/lib/libastyle.so.$solibver  | grep SONAME
objdump -p cb-clang/lib/libastyled.so.$solibver  | grep SONAME
echo cb-gcc
objdump -p cb-gcc/lib/libastyle.so.$solibver  | grep SONAME
objdump -p cb-gcc/lib/libastyled.so.$solibver  | grep SONAME
echo cb-intel
objdump -p cb-intel/lib/libastyle.so.$solibver  | grep SONAME
objdump -p cb-intel/lib/libastyled.so.$solibver  | grep SONAME


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
