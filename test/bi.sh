#!../21sh

OK="[✔]"
ERROR="[✖]"
WARNING="[ℹ]"

echo -n "cd basic "; (
  A=/tmp/a; B=/tmp/b
  P=$PWD
  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD > ${A}; cd ..; echo $PWD > ${B}; grep -Fxvf ${A} ${B} || exit 1
  echo $PWD  | grep ${P} && exit 1
  cd ${P}; pwd | grep ${P} || exit 1
) > /dev/null || echo ${ERROR} || exit 1; echo ${OK}
