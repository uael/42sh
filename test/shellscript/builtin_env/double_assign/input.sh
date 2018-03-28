env myvar=aaa myvar=123 bash -c 'echo 111$myvar; bash -c "echo 222$myvar"'
