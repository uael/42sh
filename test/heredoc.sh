OK="[✔]"
ERROR="[✖]"
WARNING="[ℹ]"

echo -n "empty heredoc "; (
  cat <<EOL
EOL
  cat <<1
1
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "multiple heredoc "; (
  cat <<EOL | grep --color=always "Hi,"; \
    cat <<EOF | grep --color=always "I'm the 21sh shell"; \
    cat <<EOF | grep --color=always "I'm trying to known"; \
    cat <<1 | grep --color=always "if heredoc are well handled or not"; \
    cat <<eoF2 | grep --color=always "here it work"
Hi,
EOL
I'm the 21sh shell
EOF
I'm trying to known
EOF
if heredoc are well handled or not
1
here it work
eoF2
) > /dev/null || echo ${ERROR} && exit 1; echo ${OK}

echo -n "heredoc subshell"; (
  env -i ${EXE} <<EOL > /dev/null
    (env | grep --color=always PATH) || exit 1
    (env | wc -l | grep --color=always 1) || exit 1
    (env | grep --color=always "PATH=usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") || exit 1
    (echo $PATH | grep --color=always "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") || exit 1
    exit 0
EOL
) || echo ${ERROR} && exit 1; echo ${OK}


echo -n "heredoc multiple subshell "; (
  env -i ${EXE} <<EOL
    (env | grep --color=always PATH) > /dev/null || exit 1
    (env | wc -l | grep --color=always 1) > /dev/null || exit 1
    (env | grep --color=always "PATH=usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
    (echo $PATH | grep --color=always "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
    exit 0
EOL
  (
    env -i ${EXE} <<EOL
      (env | grep --color=always PATH) > /dev/null || exit 1
      (env | wc -l | grep --color=always 1) > /dev/null || exit 1
      (env | grep --color=always "PATH=usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
      (echo $PATH | grep --color=always "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
      exit 0
EOL
    (
      env -i ${EXE} <<EOL
        (env | grep --color=always PATH) > /dev/null || exit 1
        (env | wc -l | grep --color=always 1) > /dev/null || exit 1
        (env | grep --color=always "PATH=usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
        (echo $PATH | grep --color=always "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
        exit 0
EOL
      (
        env -i ${EXE} <<EOL
          (env | grep --color=always PATH) > /dev/null || exit 1
          (env | wc -l | grep --color=always 1) > /dev/null || exit 1
          (env | grep --color=always "PATH=usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
          (echo $PATH | grep --color=always "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") > /dev/null || exit 1
          exit 0
EOL
      )
    )
  )
) || echo ${ERROR} && exit 1; echo ${OK}