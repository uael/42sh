echo "one cat"
echo abcde | /tmp/bin/42sh -c 'cat -e'
echo "many cats"
echo abcde | /tmp/bin/42sh -c 'cat | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
