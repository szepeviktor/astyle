# test the astyle console help display
# change the $exedir as needed

#exedir=$HOME/Projects/AStyle/build/cb-intel/bin
exedir=$HOME/Projects/AStyle/build/cb-gcc/bin

# display help
$exedir/astyle --html

echo
read -sn1 -p "Press Enter to end . . ."
