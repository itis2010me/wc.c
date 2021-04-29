#!/bin/bash

if [ ! -e ./wc ]; then
	echo "wc executable wasn't compiled successfully"
	exit 2
fi

case_num=$1
FILE_DIR=part2_files/

# Hidden: 3, 5, 9, 10, 13, 14
case "$case_num" in
	1)  ./wc ${FILE_DIR}poem.txt
		;;
	2)  ./wc -m ${FILE_DIR}values.txt
		;;
	4)  ./wc -w ${FILE_DIR}values.txt ${FILE_DIR}poem.txt
		;;
	6)  ./wc --lines ${FILE_DIR}values.txt -m ${FILE_DIR}code_demo.md -ml --chars ${FILE_DIR}pokemon.txt -w
		;;
	7)  ./wc ${FILE_DIR}poem.txt ${FILE_DIR}pokemon.txt -lw ${FILE_DIR}words
		;;
	8)  ./wc ${FILE_DIR}random2.txt ${FILE_DIR}random1.txt --words
		;;
	11) ./wc -m ${FILE_DIR}values.txt ${FILE_DIR}pokemon.txt --chars ${FILE_DIR}x --lines
		;;
	12) FILE=case12_stderr.txt
		./wc -m --words -lm -m 2> $FILE > /dev/null
		echo "Return value: $?"
		if [ -e "$FILE" ]; then
			cat $FILE
			rm $FILE
		else
			echo "Nothing was output to standard error"
		fi
		;;
	15) ./wc ${FILE_DIR}words ${FILE_DIR}poem.txt
		;;
	*)  echo "Invalid case number"
		exit 1
		;;
esac

# script credit - A. Kaloti(UCD)
