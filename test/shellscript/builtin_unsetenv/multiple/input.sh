setenv test_var1 111
setenv test_var2 222
setenv test_var3 333
env | grep test_var | sort
unsetenv test_var1 test_var2 test_var3
env | grep test_var | sort
