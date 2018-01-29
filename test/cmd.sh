#!../21sh

OK="[✔]"
ERROR="[✖]"
WARNING="[ℹ]"

echo -n "cmd basic absolute "; (
  /bin/ls | grep "21sh" || exit 1
  /bin/ls -laF | grep "CMakeLists.txt*" || exit 1
  /bin/ls -l -a -F | grep "CMakeLists.txt*" || exit 1

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "cmd basic relative "; (
  ls | grep "21sh" || exit 1
  ls -laF | grep "CMakeLists.txt*" || exit 1
  ls -l -a -F | grep "CMakeLists.txt*" || exit 1

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "cmd basic absolute no path "; (
  PATH_SAVE=$PATH; unsetenv PATH
  /bin/ls | /usr/bin/grep "21sh" || exit 1
  /bin/ls -laF | /usr/bin/grep "CMakeLists.txt*" || exit 1
  /bin/ls -l -a -F | /usr/bin/grep "CMakeLists.txt*" || exit 1
  PATH=${PATH_SAVE}

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "cmd basic relative no path "; (
  PATH_SAVE=$PATH; unsetenv PATH
  ls 2>&1 | /usr/bin/grep "not found" || exit 1
  ls -laF 2>&1 | /usr/bin/grep "not found" || exit 1
  ls -l -a -F 2>&1 | /usr/bin/grep "not found" || exit 1
  PATH=${PATH_SAVE}

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

#ls
#env | grep "PATH" || exit 1
#setenv FOO "BAr"
#env | grep "FOO=BAr" || exit 1
#unsetenv FOO
#env | grep "FOO=BAr" && exit 1
#env
#/bin/ls
#ls | cat -e
#ls -r | sort | cat -e
#base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'
#echo "Testing redirections," > /tmp/test.txt
#cat /tmp/test.txt | grep "Testing redirections," || exit 1
#echo "with multiple lines" >> /tmp/test.txt
#cat /tmp/test.txt| grep "with multiple lines" || exit 1
#wc -c < /tmp/test.txt
#cat -e << EOF
#Roses are red
#Violets are blue
#All my base are belong to you
#And so are you
#EOF
#cat -e << EOF >> /tmp/test.txt
#Roses are red
#Violets are blue
#All my base are belong to you
#And so are you
#EOF
#cat /tmp/test.txt
#ls -1; touch newfile; ls -1
#cat newfile
#ls -1; touch newfile; ls -1
#rm newfile
#mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
#cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < \
#sorted_poem > better_poem; cd -; echo "I prefer turnips anyway" >> \
#/tmp/better_poem; cat /tmp/better_poem
#Roses are red
#Violets are blue
#All my base are belong to you
#I love you
#EOF
#rm nosuchfile 2>&-
#rm nosuchfile 2>&1 | cat -e
#echo "No dollar character" 1>&2 | cat -e
#ls -1; touch newfile; ls -1
#sdf 2>&-
#exit
