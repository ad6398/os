echo "enter contents of file"
cat >first.txt # create file and read input until ctrl d

grep -v -w Dog first.txt -c #count no of lines having word Dog
