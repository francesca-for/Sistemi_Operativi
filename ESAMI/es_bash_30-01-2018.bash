#!/bin/bash

if [ "$#" -ne "2" ] ; then
     echo "Error. Expected $0 source dest"
     exit 1
fi

if [ ! -f $1 ] ; then
     echo "Error. Source is not valid file"
     exit 2
fi

if [ ! -d $2 ] ; then
     echo "Error. Dest must be a directory"
     exit 2
fi

dim=$(ls -l $1 | cut -d " " -f 5)  # dim file da copiare

usedBeforeCopy=$(df $2 | tail -n 1 | tr -s " " | cut -d " " -f 3)  # dimensione espressa in blocchi da 1KB su LINUX, 512B su Mac
let usedBeforeCopy=usedBeforeCopy*512

copied=0
cp $1 $2 &
while [ $copied -lt $dim ] ; do
     copied=$(df $2 | tail -n 1 | tr -s " " | cut -d " " -f 3)
     let copied=copied*512
     let copied=copied-usedBeforeCopy
     let perc=copied*100/size
     echo "copying file: $perc% done"
     sleep 1
done

exit 0
