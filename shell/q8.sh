#!/bin/bash

read -p "Enter Number : " n
s="*"
for((i=1;i<=$n;i++));
	do
		echo "$s"
		s="$s *"
done        
