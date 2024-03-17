#!/bin/bash
if (( $# >2 )); then
	echo "Wrong number of arguments" >&2
	exit 1
fi
#the first argument is the rules file
#rules include the lines trimmed
rules=$(sed '/^$/d' "$1" | sed '/^#/d' | sed 's/#.*//')
#good_ptks=""
og_stdin=$(cat | sed 's/ //g')
while IFS= read -r line; do
	input="$og_stdin"
	fields=$(echo "$line" | awk -F ',' '{for (i=1; i<=NF; i++) print $i}')
	for field in $fields; do
		input=$(echo "$input" | ./firewall.exe "$field")
	done
	good_ptks+="$input"$'\n'
done < <(echo "$rules")
echo "$(echo "$good_ptks" | sort -u | sed '1d')"