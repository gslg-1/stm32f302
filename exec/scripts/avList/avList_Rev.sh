#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0

REV_LOC=docs/code/review/$1
REQ_MD=docs/req/$1.JSON

if [ $# -ge 1 ] 
then
	if [ -d "$REV_LOC" ] 
	then
		if [ -f "$REQ_MD" ]
		then
			L_REV=($(ls "$REV_LOC" | sed 's/\n/ /g' | sed 's/rev_//g' | sed 's/.md//g' ))
			L_MOD=($(jq '.modules[] | .id' "$REQ_MD" | sed 's/\"//g'))
			for m in "${L_MOD[@]}"
			do
				echo ${m} > test1$m.txt
				echo "${L_MOD[@]}"
				echo "${L_REV[@]}"
				echo "${L_REV[@]}" | grep "$m"
				if [[ "${L_REV[@]}" =~ "${m}" ]]
				then
					echo "Review of $m | available"
				else
					echo "Review of $m | not available"
				fi
			done
			exit 0
		else
			echo "$REQ_MD doesn't exist."
		fi
	else
		echo "$REV_LOC doesn't exist."
	fi
else
	echo "Not enought args."
fi    
exit 1

echo 'Finished shell script' $0 '.'
#EOF