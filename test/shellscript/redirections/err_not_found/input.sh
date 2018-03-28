echo 111
cat < DOES_NOT_EXIST 2>/tmp/redir_not_exist_cat
cat -e /tmp/redir_not_exist_cat
rm -r /tmp/redir_not_exist_cat
echo 222
