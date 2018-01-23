setenv FOO bar
env | grep FOO=bar || exit 1
unsetenv FOO
env | grep FOO && exit 1
setenv FOO
env | grep FOO= || exit 1
setenv FOO
env | grep FOO= || exit 1
setenv 1 2>&1 | grep "setenv: 1: not an identifier" || exit 1
setenv FOO=bar 2>&1 | grep "setenv: Syntax error" || exit 1
setenv FOO =bar 2>&1 | grep "setenv: Syntax error" || exit 1
setenv FOO sad=bar 2>&1 | grep "setenv: Syntax error" || exit 1
