foo ()
{
	read -r mytestvar1 mytestvar2 mytestvar3 < /tmp/builtin_read_file

	export mytestvar1 mytestvar2 mytestvar3
	env | grep mytestvar | sort
}

printf 'aa bb\n' > /tmp/builtin_read_file; foo

printf '1aa\\ bb\n'  > /tmp/builtin_read_file; foo
printf '2aa\\bb\n'  > /tmp/builtin_read_file; foo
printf '3aab\n'  > /tmp/builtin_read_file; foo
printf '4aab\\'  > /tmp/builtin_read_file; foo
printf '5aa\\
5bb\n' > /tmp/builtin_read_file; foo
printf '6aa\\
6bb\\
6cc\n' > /tmp/builtin_read_file; foo

printf '7aa\\
7bb\\
7cc\n' > /tmp/builtin_read_file; foo

printf '8aa\\
8bb\\
8cc\n' > /tmp/builtin_read_file; foo
