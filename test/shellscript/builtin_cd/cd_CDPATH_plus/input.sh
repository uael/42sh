rm -rf /tmp/cd_CDPATH_plus
mkdir -p /tmp/cd_CDPATH_plus/test01/test02/test03

echo 0
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=/tmp/cd_CDPATH_plus/test01 || setenv CDPATH /tmp/cd_CDPATH_plus/test01
cd test02

echo 1
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=:test01 || setenv CDPATH :test01
cd test01
cd /tmp/cd_CDPATH_plus
cd test02

echo 2
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=test01: || setenv CDPATH test01:
cd test01
cd /tmp/cd_CDPATH_plus
cd test02

echo 3
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=: || setenv CDPATH :
cd test01

echo 4
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=:: || setenv CDPATH ::
cd test01

echo 5
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=test01/test02::test01 || setenv CDPATH test01/test02::test01
cd test01
cd /tmp/cd_CDPATH_plus
cd test02
cd /tmp/cd_CDPATH_plus
cd test03

echo 6
cd /tmp/cd_CDPATH_plus
rm -rf nosuchpath
2>&- CDPATH=nosuchpath::test01 || setenv CDPATH nosuchpath::test01
cd test01
cd /tmp/cd_CDPATH_plus
cd test02

echo 6-bis
cd /tmp
rm -rf nosuchpath
2>&- CDPATH=nosuchpath::cd_CDPATH_plus || setenv CDPATH nosuchpath::cd_CDPATH_plus
cd cd_CDPATH_plus
cd /tmp
rm -rf test01
cd test01

echo 7
cd /tmp/cd_CDPATH_plus
2>&- CDPATH=test01::nosuchpath || setenv CDPATH test01::nosuchpath
cd test01
cd /tmp/cd_CDPATH_plus
cd test02

cd /tmp
rm -rf /tmp/cd_CDPATH_plus
