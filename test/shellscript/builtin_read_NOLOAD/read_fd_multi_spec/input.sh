cat << EOF > /tmp/builtin_read_file_aa
aa bb
cc dd
ee ff
EOF
cat << EOF > /tmp/builtin_read_file_11
11 22
33 44
55 66
EOF

exec 21</tmp/builtin_read_file_aa
exec 42</tmp/builtin_read_file_11

foo ()
{
	read aa bb <&$1
	echo "$aa-$bb"
}
foo 21
foo 42
foo 21
foo 21
foo 42
foo 42
