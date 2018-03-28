echo 'def' > /tmp/redir_one_to_all
cat 9</tmp/redir_one_to_all 8<&9 7<&8 6<&7 -e 5<&6 4<&5 3<&4 <&3

rm -f /tmp/redir_one_to_all
