1>&1 cat 2&>- <<EOL > /tmp/oops.oops; 1<&- >lol cat 2>&1 <<EOF > /tmp/oops1.oops
oops
EOL
oops 2
EOF
cat Makefile 3>&1 >&3
cat Makefile 3>&1 >&3 3>&-
cat Makefile 5>&1 >&5
cat Makefile 5>&1 >&5 5>&-
cat Makefile 5>&1 >&5 5>&- >&- <&-
cat 5>&1 >&5 5>&- >&- <&- Makefile
5>&1 >&5 5>&- >&- <&- cat Makefile
5>&1 cat >&5 5>&- Makefile >&- <&-
