echo abc && echo def; echo 123 > /tmp/test_redir_file_stdout
echo ---
cat /tmp/test_redir_file_stdout

rm -f /tmp/test_redir_file_stdout
