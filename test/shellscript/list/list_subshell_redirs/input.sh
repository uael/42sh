echo 'useless commands'; (ls -1 . NO_DIR 2>/dev/null | head -n 1 | /bin/cat -e -- - NO_FILE) 2>&1 >/tmp/subshell_out_err || mkdir /tmp/useless_subshell_dir && rmdir /tmp/useless_subshell_dir; /bin/cat /tmp/subshell_out_err

rm -rf /tmp/useless_subshell_dir
rm -f /tmp/subshell_out_err
