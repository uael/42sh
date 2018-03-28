echo 'echo a | ;' > /tmp/pipe_err_parsing
/tmp/bin/42sh < /tmp/pipe_err_parsing

echo '| echo b ;' > /tmp/pipe_err_parsing
/tmp/bin/42sh < /tmp/pipe_err_parsing

echo '|' > /tmp/pipe_err_parsing
/tmp/bin/42sh < /tmp/pipe_err_parsing

echo '|;' > /tmp/pipe_err_parsing
/tmp/bin/42sh < /tmp/pipe_err_parsing

echo 'echo c\|echo d' > /tmp/pipe_err_parsing
/tmp/bin/42sh < /tmp/pipe_err_parsing

rm -f /tmp/pipe_err_parsing
