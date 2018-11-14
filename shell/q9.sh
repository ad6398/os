#!/bin/bash

read -p "Enter number : " n

if [[ $n == 1 ]]; then
	echo "1"
elif [[ $n == 2 ]]; then
	echo "1 1"
elif [[ $n == 3 ]]; then
	echo "1 1 2"
else
	tf1=1
	tf2=1
	tf3=2
	echo -n "1 1 2"
	for (( i = 3; i < n; i++ )); do
		# tf[i]=$(( tf[i-1] + tf[i-2] + tf[i-2] ))
		# tf[i]=`expr $tf[i-1] + $tf[i-2] + $tf[i-3]`
		tf4=`expr $tf1 + $tf2 + $tf3`
		echo -n " $tf4"
		tf1=$tf2
		tf2=$tf3
		tf3=$tf4
	done
fi

echo " "

# echo  ${tf[@]}