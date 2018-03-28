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

# simple quoted bang
echo === 1
echo '!!'

echo === 1.1
echo '!''!'

echo === 1.2
echo '!'!

echo === 1.3
echo !'!'

# backslashed bang
echo === 2
echo \!\!

echo === 2.1
echo \!!

echo === 2.2
echo !\!

echo === 2.3
echo !!\a

echo === 2.4
echo \a!!

"echo" toto

# bash tests
echo 2
echo '!'
echo 3
echo '!!'
echo 4
echo "! "
echo 5
echo "!" "
echo 6
echo "\!"
echo 7
echo "\!\!"
echo 8
echo "!!"
echo 9
echo " !!"
echo 10
echo "!! "
echo 11
echo "! ! "
echo 12
echo \'!!
echo 13
echo "'!!'"
echo 14
echo '<
!!
>'
echo 15
echo "<
!!
>"
