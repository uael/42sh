IFS=xyz
echo -n "aaxbb" > /tmp/builtin_read_file

read mytestvar1 mytestvar2 < /tmp/builtin_read_file

export mytestvar1 mytestvar2
env | grep mytestvar | sort

echo -n "aaxbbycc" > /tmp/builtin_read_file

read mytestvar1 mytestvar2 < /tmp/builtin_read_file

export mytestvar1 mytestvar2
env | grep mytestvar | sort
