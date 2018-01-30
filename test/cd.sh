P=$PWD
cd ////
cd ///
cd //
cd /
cd ${P}
cd include
cd ush
cd -
cd
cd
cd -
cd /////tmp
cd + 2>&1 | grep -o "cd: +: No such file or directory"
cd lol 2>&1 | grep -o "cd: lol: No such file or directory"
cd -88qweqfwqwqeqwe 2>&1 | grep -o "cd: -8: invalid option
cd: usage: cd [-L|-P] [dir]"
cd -qwd qw6 2>&1 | grep -o "cd: -q: invalid option
cd: usage: cd [-L|-P] [dir]"
cd ${P}
cd Makefile 2>&1 | grep -o "cd: Makefile: Not a directory"
ln -s s1 s2 &> /dev/null
ln -s s2 s3 &> /dev/null
ln -s s3 s1 &> /dev/null
cd s1 2>&1 | grep -o "cd: s1: Too many levels of symbolic links"
cd ./s1 2>&1 | grep -o "cd: ./s1: Too many levels of symbolic links"
rm -f s1 s2 s3
