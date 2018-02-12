1>&1 cat 2&>- <<EOL > /dev/null; 1<&- >lol cat 2>&1 <<EOF >
oops
EOL
oops 2
EOF
