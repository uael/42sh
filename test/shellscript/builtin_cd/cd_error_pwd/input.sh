env -i ./42sh -c "cd . ; /bin/pwd ;"

cd /tmp
rm -rf toto
mkdir toto

2>/dev/null unset PWD || unsetenv PWD
cd toto
pwd
cd -- -

2>/dev/null PWD="tata" || setenv PWD "tata"
cd toto
pwd
cd -- -
rm -rf toto

2>&- cd tutu
cd /tmp
cd -
pwd

cd /tmp/toto
rm -rf /tmp/toto
cd -P .
