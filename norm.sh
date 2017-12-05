#!/usr/bin/env bash

OK="\033[32m[✔]\033[0m"
ERROR="\033[31m[✖]\033[0m"
WARNING="\033[34m[ℹ]\033[0m"

function padme {
  S="$1"
  line='.............................'
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
  $($3 > ${OUT} 2>&1) &
  pid=$!
  spinner ${pid}
  wait ${pid}
  if [[ $? != 0 ]]; then
      echo -e "${ERROR} $(cat ${OUT})"
  else
      echo -e "${OK}"
  fi
}

NORM_OUT=$(mktemp)
function norm_file {
  local norm_out=$(/usr/bin/norminette $1)
  out=$(echo "$norm_out" | grep -E '^(Error|Warning)' | sed ''/Error/s//$(printf "\033[31mError\033[0m")/'')
  if [[ ! -z ${out} ]]; then
    echo -e "$(padme "Norm: $(basename $1)") $ERROR\n$out" >> ${NORM_OUT}
  fi
}

PROJECT_PATH='.'

function donorm {
  local pids=""
  for file in $*; do
    norm_file ${file} &
    pids="$pids $!"
  done
  wait ${pids}
  out=$(cat ${NORM_OUT})
  if [[ ! -z ${out} ]]; then
    echo -e "\n$out"
    exit 1
  fi
  exit 0
}

mkdir -p out
job "Norm" "all" "donorm $*"

rm ${OUT}
rm ${NORM_OUT}
