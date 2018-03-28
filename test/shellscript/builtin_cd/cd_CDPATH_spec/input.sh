mkdir -p /tmp/test_builtin_cd_folder
2>&- export CDPATH=/tmp || setenv CDPATH /tmp
cd /
pwd
cd test_builtin_cd_folder
pwd

2>&- unset CDPATH || unsetenv CDPATH
mkdir /tmp/bash-dir-a
2>&- export CDPATH=.:/tmp || setenv CDPATH .:/tmp
cd bash-dir-a
pwd
printenv PWD

# cleanup
cd /
rmdir  /tmp/bash-dir-a
rm -rf /tmp/test_builtin_cd_folder
