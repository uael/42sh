# simple output
echo abc > /tmp/redir-test
cat /tmp/redir-test
rm /tmp/redir-test

# this should be an error
/bin/cat < "a b"

# duplicating to stdout
4>/tmp/bash-a echo to a 1>&4
5>/tmp/bash-b echo to b 1>&5
cat /tmp/bash-a
cat /tmp/bash-b
6<>/tmp/bash-c echo to c 1>&6
cat /tmp/bash-c

rm -f /tmp/bash-a /tmp/bash-b /tmp/bash-c

# various forms of null redirection
pwd > /tmp/null-redir-a
[ -f /tmp/null-redir-a ] && rm /tmp/null-redir-a || echo oops

( pwd > /tmp/null-redir-c )
[ -f /tmp/null-redir-c ] && rm /tmp/null-redir-c || echo oops

exit 3 | pwd > /tmp/null-redir-e
[ -f /tmp/null-redir-e ] && rm /tmp/null-redir-e || echo oops

# These should not echo anything
( ( echo hello 1>&3 ) 3>&1 ) >/dev/null 2>&1
( ( echo hello 1>&3 ) 3>&1 ) >/dev/null 2>&1 | cat -e
cat > /tmp/shells-heredoc <<EOF -e
			/bin/bash
   			/bin/csh
        	/bin/ksh
 	 	 	/bin/sh
	 	 	/bin/tcsh
/bin/zsh				
EOF
rm -f /tmp/shells-heredoc 
sh << "EOF"
#! /bin/sh
echo $#
echo in script
EOF
