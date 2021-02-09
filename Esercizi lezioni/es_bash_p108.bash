#!/bin/bash

if [ "$#" -ne "1" ] ; then
        echo "Error. Expected: script_exe filename.txt"
        exit 1
fi

echo "Results:"

while read row ; do
	pos=1
	f=0
	for num in $row ; do
		if [ "$pos" -eq "1" ] ; then
			let f=f+3*num*num
		elif [ "$pos" -eq "2" ] ; then
			let f=f+4*num
		elif [ "$pos" -eq "3" ] ; then
			let f=f+5*num
		fi
		let pos=pos+1
	done
	echo "$f"
done < "$1"

exit 0
