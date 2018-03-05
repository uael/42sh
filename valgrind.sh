#!/usr/bin/env bash

OK="\033[32m ✔ \033[0m"
ERROR="\033[31m ✖ \033[0m"
WARNING="\033[34m ℹ \033[0m"

function padme {
  S="$1"
  line='                 '
  printf "%s %s" "$S" "${line:${#S}}"
}

OUT=$(mktemp)
function job {
  echo -en "$(padme "$1: $2") "
  ($3 &> ${OUT}) &
  pid=$!
  wait ${pid}
  local RET=$?
  if [[ $RET != 0 ]]; then
    echo -e "${ERROR} $(cat ${OUT})"
  else
    echo -e "${OK}"
  fi
  return $RET
}

function dovalgrind {
  valgrind --leak-check=full --track-origins=yes \
    --suppressions=./valgrind.supp $1 $2 \
    &> ${OUT}
  ! cat ${OUT} | grep "definitely lost: [1-9]"
  return $?
}

if [ -z "$1" ]; then
  PROJECT_PATH='.'
else
  PROJECT_PATH=$1
fi

if [ -z "$2" ];then
  export EXE=${PROJECT_PATH}/42sh
else
  export EXE=${PROJECT_PATH}/$2
fi

mkdir -p out
ECODE=0
for test in ./test/*.sh; do
  job "Leaks" "$(basename "${test%.*}")" "dovalgrind ${EXE} ${test}"
  RET=$?
  if [[ $RET != 0 ]]; then
    ECODE=$RET
  fi
done

rm ${OUT}
exit $ECODE
