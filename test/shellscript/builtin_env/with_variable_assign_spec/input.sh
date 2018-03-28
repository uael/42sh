setenv env_test_var 456
env env_test_var=123 bash -c 'env | grep env_test_var'
