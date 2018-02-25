cat <<EOL
EOL
cat <<1
1

cat <<! <<!
a
!
b
!

cat <<EOL | grep -o "Hi,"; \
  cat <<EOF | grep -o "I'm the 42sh shell"; \
  cat <<EOF | grep -o "I'm trying to known"; \
  cat <<1 | grep -o "if heredoc are well handled or not"; \
  cat <<eoF2 | grep -o "here it work"
Hi,
EOL
I'm the 42sh shell
EOF
I'm trying to known
EOF
if heredoc are well handled or not
1
here it work
eoF2
