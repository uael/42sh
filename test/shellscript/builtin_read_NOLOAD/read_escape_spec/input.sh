echo -n 'a\\a \$b\b c\@\"c' > /tmp/builtin_read_file

read mytestvar1 mytestvar2 < /tmp/builtin_read_file

export mytestvar1 mytestvar2
env | grep mytestvar | sort
