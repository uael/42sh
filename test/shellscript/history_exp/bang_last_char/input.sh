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

# last char
echo === 1
echo abc !!

echo === 1.1
echo abc !

echo === 1.2
echo abc !! 

echo === 1.3
echo abc ! 
