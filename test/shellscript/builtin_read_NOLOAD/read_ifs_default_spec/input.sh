
foo () {
	echo "case ifs ="
	echo "{$IFS}"
	printf "1a 2b\t3c\t4d 5e\n6f 7g" > /tmp/builtin_read_file
	read mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5 < /tmp/builtin_read_file
	export mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5
	env | grep mytestvar | sort
	echo
}
foo
IFS="`printf '\t'`"
foo
IFS="bdf"
foo
