echo '======= case 1'
echo "aa\
bb"

echo '======= case 2'
echo "complementary cases"
( echo a\
b)

echo '======= case 3'
echo "a\
b"

echo '======= case 4'
echo 'a
b'

echo '======= case 5'
echo "'a\
b'"

echo '======= case 6'
echo a\\
echo b

echo '======= case 7'
(echo a\
echo b\
echo c\
printf d)

echo "====== test 1"
echo abc | \
cat -e | \
wc

echo "====== test 2"
echo aa\\\\\
bb

echo "====== test 3"
echo aa\\\\\
bb \\\
cc

echo "====== test 4"
echo 'aa\
bb'

echo "====== test 5"
echo 'aa\\
bb'

echo "====== test 6"
echo 'aa\\\
bb'

echo "====== test 7"
echo \''aa\\\
bb'\'
