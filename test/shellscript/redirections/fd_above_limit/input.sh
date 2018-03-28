cd /tmp
echo abc 10>&-
echo def 11>&-
echo ghi 10>fd_above_limit
cat -e fd_above_limit
rm -f fd_above_limit
