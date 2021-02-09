#!/bin/bash

i=0
echo "Values: "
while [ 0 ] ; do
	read n
	if [ "$n" -eq "0" ] ; then
		break
	else
		vett[i]=$n
	fi
	let i=i+1
done

let i=i-1
while [ "$i" -ge "0" ] ; do
	echo -n "${vett[i]} "
	let i=i-1
done

exit 0
