setenv test_var abc
unsetenv * test_var does_not_exist
env
setenv test_var def
env
