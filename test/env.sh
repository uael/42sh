env FOO=barr 2>&1 | grep -o "FOO=bar"
env FOO=bar -uFOO 2>&1 | grep -o "FOO=bar"
env -uFOO FOO=bar 2>&1 | grep -o "FOO=bar"
env -PBAR FOO=bar -uFOO 2>&1 | grep -o "FOO=bar"
env -i FOO=bar -uFOO 2>&1 | grep -o "FOO=bar"
env -i -uFOO FOO=bar 2>&1 | grep -o "FOO=bar"
env -i env 2>&1 | grep -o "PATH"
env 2>&1 2>&1 | grep -o "home"
(env) | grep -o "PATH"
#alias setenv="export"
#alias unsetenv="unset"
#setenv FOO bar
#unsetenv FOO
#env 2>&1 | grep -o FOO
#setenv FOO bar
#env 2>&1 | grep -o FOO
