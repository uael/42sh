cd 42sh 2>&1 | grep -o "cd: 42sh: No a directory"
cd .gitignore 2>&1 | grep -o "cd: 42sh: No a directory"
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
A=/tmp/a.diff; B=/tmp/b.diff
P=$PWD
echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B}
echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B}
echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B}
echo $PWD | grep ${P}
cd ${P}; pwd | grep ${P}
echo $PWD | grep ${P}
A=/tmp/a; B=/tmp/b
P=$PWD
cd /tmp; \
  echo $PWD | grep "/tmp"; \
  echo $OLDPWD | grep ${P}; \
  cd -; echo $PWD; \
  echo $PWD | grep ${P}; \
  echo $OLDPWD | grep "/tmp"; \
  echo $PWD | grep ${P}
cd ${P}; pwd | grep ${P}
echo $PWD | grep ${P}
