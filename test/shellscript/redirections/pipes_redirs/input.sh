echo lol | wc -l | xargs echo > /tmp/testfile
cat /tmp/testfile
cat -e < /tmp/testfile | wc -c | xargs echo
cat -e < /tmp/testfile | wc -c | xargs echo > /tmp/testfile2
cat /tmp/testfile2
rm /tmp/testfile /tmp/testfile2
