IFS=_
echo -n 'aa\_bb_cc' > /tmp/builtin_read_file

read mytestvar1 mytestvar2 < /tmp/builtin_read_file

export mytestvar1 mytestvar2
env | grep mytestvar | sort
