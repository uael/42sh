cat << EOF > /tmp/builtin_read_file
aa bb
11 22
xx yy
EOF

exec 42</tmp/builtin_read_file

while read aa bb <&42
do
	echo "$bb-$aa"
done
