cd /tmp
pwd
cd -- -

cd /tmp
pwd
cd -P -- -
cd -P -- -

cd -P /tmp
pwd
cd -- -
pwd

rm -rf /tmp/toto
mkdir /tmp/toto

cd /tmp
cd /tmp/toto
cd ..
pwd
cd -- -
pwd

cd /tmp
rm -rf /tmp/toto
