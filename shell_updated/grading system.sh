#!/bin/sh
echo "Enter  mark for the student"
read m
echo -n "The grade of the student is:" # -n new line
if [ $m -ge 90 -a $m -le 100 ]; then # (-ge ,>=) (-le,<=) (-a,and)
	echo "A"
elif [ $m -ge 70 -a $m -le 89 ]; then
	echo "B"
elif [ $m -ge 40 -a $m -le 69 ]; then
	echo "C"
else
	echo "F"
fi

