mkdir -p /tmp/test_cd_builtin/mydir
ln -s /tmp/test_cd_builtin/mydir /tmp/test_cd_builtin/mydir_sym

echo
echo "cd /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd /tmp/test_cd_builtin/mydir_sym
pwd

echo
echo "cd -P /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -P /tmp/test_cd_builtin/mydir_sym

echo
echo "cd -L /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -L /tmp/test_cd_builtin/mydir_sym
pwd

echo
echo "cd -- /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -- /tmp/test_cd_builtin/mydir_sym
pwd

echo
echo "cd -P -- /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -P -- /tmp/test_cd_builtin/mydir_sym

echo
echo "cd -L -- /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -L -- /tmp/test_cd_builtin/mydir_sym
pwd

cd /
rm -rf /tmp/test_cd_builtin
