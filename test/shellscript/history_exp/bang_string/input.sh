# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
cd /tmp
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file
echo "test1"

\echo "======== EXP ========"

!e
!ech
!echo d
!echoo d
echo !p !e

!ech\
o

'echo' test2
!'ech

