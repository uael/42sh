cat gnuk 2> /tmp/testfile
cat /tmp/testfile
cat gnuk 2>&1 | cat -e
rm /tmp/testfile
cat bouh >& /tmp/testfile
cat -e /tmp/testfile
rm /tmp/testfile
