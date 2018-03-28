echo aaa > /tmp/redir_op;echo bbb >> /tmp/redir_op;echo ccc >> /tmp/redir_op
cat -e < /tmp/redir_op
echo ddd

rm -f /tmp/redir_op
