#!/bin/bash

if [ $# -ne 2 ] ; then
	echo -n "Values: "
	read nr nc
else
	nr=$1
	nc=$2
fi

x=0

r=0
while [ $r -lt $nr ] ; do
	c=0
	while [ $c -lt $nc ] ; do
		echo -n "$x "
		let c=c+1
		let x=x+1
	done
	let r=r+1
	echo ""
done

exit 0
