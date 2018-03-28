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

# echo double bang, no quote
echo === 1
echo !!

echo === 1.1
echo ! !

echo === 1.2
echo !! a

echo === 1.3
echo a !!

echo === 1.4
echo !!a

echo === 1.5
echo a!!

echo === 1.6
echo a!!a

# double bang
echo === 2
!!

echo === 2.1
!!a

echo === 2.2
!!!!!!

echo === 2.3
!!!!!!!

echo === 2.4
!! ! !!! ! !!!! !! !
