foo ()
{
	printf $1 > /tmp/builtin_read_file

	cat /tmp/builtin_read_file
	echo
	read mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5 < /tmp/builtin_read_file

	export mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5
	env | grep mytestvar | sort
}

foo 'a%sa bb \\\nc%sc dd'
