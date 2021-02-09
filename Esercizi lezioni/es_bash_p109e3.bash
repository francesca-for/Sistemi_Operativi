#!/bin/bash

if [ $# -ne 1 ] ; then 
	echo "Error. Expected prgrm filename"
	exit 1
fi

file="tmpfile"
touch "$file"

while read n1 n2 ; do
	echo "$n2 $n1"
done < $1 > $file

rm "$1"
mv "$file" "$1"

exit 0
