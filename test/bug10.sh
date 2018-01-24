echo >&- 2>&- | wc | grep "0       0       0" || exit 1
/a | cat /dev/random | base64 > tutu | grep "/a: Command not found" || exit 1