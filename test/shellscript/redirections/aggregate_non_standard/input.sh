echo abc > /tmp/redir_aggregate_non_standard
cat 4</tmp/redir_aggregate_non_standard <&4

rm -f /tmp/redir_aggregate_non_standard
