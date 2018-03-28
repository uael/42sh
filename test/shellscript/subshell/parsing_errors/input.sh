echo '()' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(;)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(|)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(>)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(&&)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo a;)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo b &&)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo b && > /tmp/subshell_err_zut)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo c |)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo c | >> /tmp/subshell_err_zut)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo d; ())' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(echo d; (echo d2;));' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

echo '(;echo e)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing

rm -f /tmp/subshell_err_parsing
rm -f /tmp/subshell_err_zut
