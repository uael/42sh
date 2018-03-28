mkdir -p /tmp/test_cd_builtin/mydir
ln -s /tmp/test_cd_builtin/mydir /tmp/test_cd_builtin/mydir_sym1
ln -s /tmp/test_cd_builtin/mydir_sym1 /tmp/test_cd_builtin/mydir_sym2

cd /tmp/test_cd_builtin && cd mydir_sym1
pwd
cd -P /tmp/test_cd_builtin && cd mydir_sym1
pwd
cd -L /tmp/test_cd_builtin && cd mydir_sym1
pwd

cd /tmp/test_cd_builtin && cd mydir_sym2
pwd
cd -P /tmp/test_cd_builtin && cd mydir_sym2
pwd
cd -L /tmp/test_cd_builtin && cd mydir_sym2
pwd

cd /
rm -rf /tmp/test_cd_builtin
