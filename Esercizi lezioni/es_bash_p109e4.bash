#!/bin/bash

if [ "$#" -lt 2 ] ; then
	echo "Error. Run: $0 dirName file1 ... fileN"
	exit 1
fi

if [ ! -d $1 ] ; then
	mkdir $1
fi

dir=$1
shift
for file in $* ; do
	echo -n "Copy $file in $dir (y/n)? "
	read ans
	if [ "$ans" = "y" ] ; then
		cp $file $dir
		if [ $? -eq "0" ] ;  then
			echo "-> Copy done for $dir/$file"
		else
			echo "-> Copy error for $dir/$file"
		fi
	elif [ "$ans" = "n" ] ; then
		continue
	else
		echo "This option is not valid. File not copied"
	fi
done

exit 0
