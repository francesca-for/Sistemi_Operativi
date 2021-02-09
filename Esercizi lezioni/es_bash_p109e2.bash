#!/bin/bash

for x in $(find . -type f -maxdepth 1 -regex ".*\.c") ; do
	grep -l POSIX "$x"
done 

echo "--seconda versione--"

for x in $(find . -type f -maxdepth 1 -regex ".*\.c" -exec grep -l -e "POSIX" {} ';') ; do
	echo "$x"
done

exit 0
