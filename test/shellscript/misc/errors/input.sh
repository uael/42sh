# bad option
env -x abc

# cannot set invalid identifiers
setenv /bin/sh

# various `cd' errors
( unsetenv HOME ; cd )
( setenv HOME /tmp/xyz.bash ; cd )

# errors from cd
cd /bin/sh	# error - not a directory
setenv OLDPWD /tmp/cd-notthere
cd -

# redirection errors
echo 9<no_such_file || echo TEST
