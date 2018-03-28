(echo foo; echo bar; ls DO_NOT_EXIST) > /tmp/test_subshell_file 2> /tmp/test_subshell_file_err
echo -------
cat /tmp/test_subshell_file
cat /tmp/test_subshell_file_err
echo -------

rm -f /tmp/test_subshell_file
rm -f /tmp/test_subshell_file_err
