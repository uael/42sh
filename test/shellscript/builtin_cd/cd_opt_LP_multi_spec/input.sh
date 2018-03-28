mkdir -p /tmp/test_cd_builtin/mydir
ln -s /tmp/test_cd_builtin/mydir /tmp/test_cd_builtin/mydir_sym

echo
echo "cd -LP /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -LP /tmp/test_cd_builtin/mydir_sym
pwd

echo
echo "cd -LPLP /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -LPLP /tmp/test_cd_builtin/mydir_sym
pwd

echo
echo "cd -PL /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -PL /tmp/test_cd_builtin/mydir_sym
pwd


echo
echo "cd -PPPLPL /tmp/test_cd_builtin/mydir_sym"
cd /tmp/test_cd_builtin && cd -PPPLPL /tmp/test_cd_builtin/mydir_sym
pwd

cd /
rm -rf /tmp/test_cd_builtin
