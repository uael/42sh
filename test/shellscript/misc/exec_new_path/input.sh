mkdir -p /tmp/test_binary_path
echo "echo abc" > /tmp/test_binary_path/myexec
chmod 755 /tmp/test_binary_path/myexec

# Fail
echo 1 fail >&2
myexec

# Pass
echo 2 pass
2>&- export PATH="/tmp/test_binary_path:/usr/bin:/bin" || setenv PATH "/tmp/test_binary_path:/usr/bin:/bin"
myexec

# Pass
echo 3 pass
/tmp/test_binary_path/myexec

# Pass
echo 4 pass
cd /tmp/test_binary_path
myexec

# Fail
echo 5 fail >&2
2>&- unset PATH || unsetenv PATH
myexec

# Fail
echo 6 fail >&2
./test_binary_path/myexec

# Fail
echo 7 fail >&2
cd /tmp/test_binary_path
myexec

cd /tmp
/bin/rm -rf /tmp/test_binary_path
