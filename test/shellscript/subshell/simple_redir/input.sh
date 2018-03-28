echo "============= 1"
true; (echo abc) > /tmp/subshell_compound_redirs_spec_file1
echo "============= 2"
cat /tmp/subshell_compound_redirs_spec_file1
echo "============= 3"
false; (echo 123) > /tmp/subshell_compound_redirs_spec_file2
echo "============= 4"
cat /tmp/subshell_compound_redirs_spec_file2
echo "============= 5"

rm -f /tmp/subshell_compound_redirs_spec_file1
rm -f /tmp/subshell_compound_redirs_spec_file2
