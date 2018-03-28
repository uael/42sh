echo 'abc' >/tmp/pipe_redir
ls | cat -e < /tmp/pipe_redir | cat -e

echo 'def' | cat -e 3<>/tmp/pipe_redir_fd >&3 | cat -e <&3
cat /tmp/pipe_redir_fd

rm -f /tmp/pipe_redir
rm -f /tmp/pipe_redir_fd
