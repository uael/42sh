ush: syntax error: Expected `<word>' after redirection `>' got `<newline>'
1>&1 cat 2>&- <<EOL > /dev/null; 1<&- >/tmp/lol cat 2>&1 <<EOF >
                                                                ^
