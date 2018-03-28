cat << EOF | /tmp/bin/42sh
echo abc | wc
echo 123 | cat -e | cat -e | cat -e
env | sort | grep -v PS1 PS2
EOF
