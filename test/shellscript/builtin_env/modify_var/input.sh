setenv env_foo_1 bar1
echo ===== 1
env env_foo_2=bar2 env | grep env_foo_
echo ===== 2
env -i env_foo_2=bar3 env | grep env_foo_
