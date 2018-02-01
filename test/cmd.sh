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
  /bin/ls || exit 1
  /bin/ls -laF || exit 1
  /bin/ls -l -a -F || exit 1
  PATH=${PATH_SAVE}

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "cmd basic relative no path "; (
  PATH_SAVE=$PATH; unsetenv PATH
  ls 2>&1 && exit 1
  ls -laF 2>&1 && exit 1
  ls -l -a -F 2>&1 && exit 1
  PATH=${PATH_SAVE}

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}
