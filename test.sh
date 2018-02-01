#!/usr/bin/env bash

OK="\033[32m[✔]\033[0m"
ERROR="\033[31m[✖]\033[0m"
WARNING="\033[34m[ℹ]\033[0m"

function padme {
  S="$1"
  line='                            '
  printf "%s %s" "$S" "${line:${#S}}"
}

function spinner {
  local FRAMES='|/-\'
  while [ ! -z "$(ps a | awk '{print $1}' | grep $1)" ];
  do
    printf "\033[34m[%c]\033[0m" "$FRAMES"
    local TMP=${FRAMES#?}
    FRAMES=${TMP}${FRAMES%"$TMP"}
    sleep 0.2
    printf "\b\b\b"
  done
}

OUT=$(mktemp)
function job {
  echo -en "$(padme "$1: $2") "
  ($3 &> ${OUT}) &
  pid=$!
  spinner ${pid}
  wait ${pid}
  local RET=$?
  if [[ $RET != 0 ]]; then
    echo -e "${ERROR} $(cat ${OUT})"
  else
    echo -e "${OK}"
  fi
  return $RET
}

if [ -z "$1" ]; then
  PROJECT_PATH='.'
else
  PROJECT_PATH=$1
fi

if [ -z "$2" ];then
  export EXE=${PROJECT_PATH}/21sh
else
  export EXE=${PROJECT_PATH}/$2
fi

function dotest {
  local test=$3
  local test_out="./out/$(basename "${test%.*}").out"
  local test_expected="./test/$(basename "${test%.*}").ex"
  if [ ! -f ${test_expected} ]; then
    test_expected="./out/$(basename "${test%.*}").ex"
    rm -f ${test_expected}
    $2 ${test} &> ${test_expected}
  fi
  rm -f ${test_out}
  $1 ${test} &> ${test_out}
  diff ${test_out} ${test_expected}
}

mkdir -p out
ECODE=0
for test in ./test/*.sh; do
  job "Test" "$(basename "${test%.*}")" "dotest ${EXE} /bin/bash ${test}"
  RET=$?
  if [[ $RET != 0 ]]; then
    ECODE=$RET
  fi
done

rm ${OUT}
exit $ECODE
