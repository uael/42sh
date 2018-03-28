# simple output
rm -f /tmp/redir_no_cmd
> /tmp/redir_no_cmd
file /tmp/redir_no_cmd
rm -f /tmp/redir_no_cmd

# replace existing file
bash -c "echo abc > /tmp/redir_no_cmd"
cat -e /tmp/redir_no_cmd
> /tmp/redir_no_cmd
cat -e /tmp/redir_no_cmd
wc /tmp/redir_no_cmd

# multiple creation file
> /tmp/redir_no_cmd_file1 > /tmp/redir_no_cmd_file2 > /tmp/redir_no_cmd_file3

# append, no replace
rm -f /tmp/redir_no_cmd_input_append
echo 'def' > /tmp/redir_no_cmd_input_append
cat -e /tmp/redir_no_cmd_input_append
>> /tmp/redir_no_cmd_input_append

# input does not exist, err msg
rm -f /tmp/redir_no_cmd_input
< /tmp/redir_no_cmd_input
echo 'abc' > /tmp/redir_no_cmd_input
< /tmp/redir_no_cmd_input

# heredoc
<<EOF
abc
def
EOF

# duplicating
<&0
<&1
<&2
<&3
>&0
>&1
>&2
>&3
<&0 <&1 <&2 >&0 >&1 >&2
<&0 <&1 <&2 <&3 >&0 >&1 >&2 >&3

# input-output
rm -f /tmp/redir_no_cmd_input_output
<>/tmp/redir_no_cmd_input_output
rm -f /tmp/redir_no_cmd_input_output
0<>/tmp/redir_no_cmd_input_output
rm -f /tmp/redir_no_cmd_input_output
1<>/tmp/redir_no_cmd_input_output
rm -f /tmp/redir_no_cmd_input_output
2<>/tmp/redir_no_cmd_input_output
rm -f /tmp/redir_no_cmd_input_output
3<>/tmp/redir_no_cmd_input_output

# pipe
ls | > /tmp/redir_no_cmd_in_pipe | cat -e;				rm -f /tmp/redir_no_cmd_in_pipe
> /tmp/redir_no_cmd_in_pipe | echo 'pipe' | cat -e;		rm -f /tmp/redir_no_cmd_in_pipe
ls | cat -e | > /tmp/redir_no_cmd_in_pipe;				rm -f /tmp/redir_no_cmd_in_pipe

# subshell
(>/tmp/redir_no_cmd_in_subshell1)
(>/tmp/redir_no_cmd_in_subshell2;)
(>/tmp/redir_no_cmd_in_subshell3);
(>/tmp/redir_no_cmd_in_subshell4;);

# cleanup
rm -rf /tmp/redir_no_cmd
rm -rf /tmp/redir_no_cmd_file1
rm -rf /tmp/redir_no_cmd_file2
rm -rf /tmp/redir_no_cmd_file3
rm -rf /tmp/redir_no_cmd_input_append
rm -rf /tmp/redir_no_cmd_input_output
rm -rf /tmp/redir_no_cmd_input
rm -rf /tmp/redir_no_cmd_in_pipe
rm -rf /tmp/redir_no_cmd_in_subshell1
rm -rf /tmp/redir_no_cmd_in_subshell2
rm -rf /tmp/redir_no_cmd_in_subshell3
rm -rf /tmp/redir_no_cmd_in_subshell4
