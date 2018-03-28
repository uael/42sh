python -c 'print "aabbcc\n"*45' > /tmp/builtin_read_file

while read -r xx yy
do
	if [ ! -z "$yy" ]; then
    	printf "%s %s\n" "$yy" "$xx"
	fi
done < /tmp/builtin_read_file
