#!../21sh

OK="[✔]"
ERROR="[✖]"
WARNING="[ℹ]"

echo -n "cd basic "; (
  A=/tmp/a.diff; B=/tmp/b.diff
  P=$PWD

  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD  | grep ${P} && exit 1

  cd ${P}; pwd | grep ${P} || exit 1
  echo $PWD | grep ${P} || exit 1

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "cd complex "; (
  A=/tmp/a; B=/tmp/b
  P=$PWD

  cd /Users; \
    echo $PWD | grep "/Users" || exit 1; \
    echo $OLDPWD | grep ${P} || exit 1; \
    cd -; echo $PWD; \
    echo $PWD | grep ${P} || exit 1; \
    echo $OLDPWD | grep "/Users" || exit 1; \
    echo $PWD | grep ${P} || exit 1

  cd /tmp; \
    echo $PWD | grep "/tmp" || exit 1; \
    echo $OLDPWD | grep ${P} || exit 1; \
    cd -; echo $PWD; \
    echo $PWD | grep ${P} || exit 1; \
    echo $OLDPWD | grep "/tmp" || exit 1; \
    echo $PWD | grep ${P} || exit 1

  cd ${P}; pwd | grep ${P} || exit 1
  echo $PWD | grep ${P} || exit 1

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "env "; (
  env | grep "PATH" || exit 1
  setenv FOO "bar"
  env | grep "FOO=bar" || exit 1
  unsetenv FOO
  env | grep "FOO=bar" && exit 1

  exit 0
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}
