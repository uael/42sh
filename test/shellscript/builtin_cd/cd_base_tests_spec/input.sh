cd /tmp
echo "======= 1"
cd /
echo "======= 2"
pwd
echo "======= 3"
cd -- -
echo "======= 4"
rm -rf test1_cd
echo "======= 5"
rm -rf test2_cd
echo "======= 6"
mkdir test1_cd
echo "======= 7"
cd test1_cd
echo "======= 8"
ls -a | cat -e
echo "======= 9"
cd ..
echo "======= 10"
ln -s test1_cd test2_cd
echo "======= 11"
cd -P test2_cd
echo "======= 12"
pwd | grep test1
echo "======= 13"
cd ..
echo "======= 14"
cd -P test2_cd
echo "======= 15"
pwd | grep test2
echo "======= 16"
cd ..
echo "======= 17"
rm -rf test1_cd
echo "======= 18"
rm -rf test2_cd
echo "======= 19"
