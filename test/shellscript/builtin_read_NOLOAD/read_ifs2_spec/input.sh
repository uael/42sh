IFS=x
echo -n "aaxxbbxxxcc  ddxx" > /tmp/builtin_read_file

read mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5 < /tmp/builtin_read_file

export mytestvar1 mytestvar2 mytestvar3 mytestvar4 mytestvar5
env | grep mytestvar | sort
