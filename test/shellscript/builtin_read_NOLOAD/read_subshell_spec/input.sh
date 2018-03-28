(read foo << EOF && echo $foo
fooAA BB
EOF
)
echo "-$foo-"

{
read bar << EOF && echo $bar
bar11 22
EOF
}
echo "-$bar-"
