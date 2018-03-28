# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
cd /tmp
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file

echo bang
!! !e !p !3 !-1 !! end

echo bang-bang
!-1abc!!def!!!12-1!echo end
