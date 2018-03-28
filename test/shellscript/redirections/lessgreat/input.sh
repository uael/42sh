# input
echo 'abc' > /tmp/redir_lessgreat_file
/bin/cat 3<>/tmp/redir_lessgreat_file <&3 -e

# output
echo 'def' | cat 3<>/tmp/redir_lessgreat_file >&3 -e
/bin/cat -e /tmp/redir_lessgreat_file

# both
echo 'ghi' > /tmp/redir_lessgreat_file
( cat <&4 ; echo zzzz >&4 ) 4<>/tmp/redir_lessgreat_file
cat -e /tmp/redir_lessgreat_file

rm -f /tmp/redir_lessgreat_file
