echo merde > /tmp/redir_echo_in
cat 3</tmp/redir_echo_in <&3

rm -f /tmp/redir_echo_in
