echo 'abc' > /tmp/redir_stdin_close

# with binary
/bin/cat -e <&- </tmp/redir_stdin_close

# with builtin
echo 'def' <&- </tmp/redir_stdin_close

echo end
cat -e /tmp/redir_stdin_close

rm -f /tmp/redir_stdin_close
