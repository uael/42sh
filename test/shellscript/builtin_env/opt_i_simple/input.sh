setenv foo bar
echo ===== 1
env env | grep foo
echo ===== 2
env -i env | grep foo
env -i echo bla
echo bli
