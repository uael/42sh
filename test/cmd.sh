/bin/ls | grep -o "42sh"
/bin/ls -laF | grep -o "CMakeLists.txt*"
/bin/ls -l -a -F | grep -o "CMakeLists.txt*"
ls | grep "42sh"
ls -laF | grep -o "CMakeLists.txt*"
ls -l -a -F | grep -o "CMakeLists.txt*"
GREP=$(which grep)
unset PATH
/bin/ls | ${GREP} -o "42sh"
/bin/ls -laF | ${GREP} -o "CMakeLists.txt*"
/bin/ls -l -a -F | ${GREP} -o "CMakeLists.txt*"
ls 2>&1 | ${GREP} -o "ls"
ls -laF 2>&1 | ${GREP} -o "ls"
ls -l -a -F 2>&1 |${GREP} -o "ls"
