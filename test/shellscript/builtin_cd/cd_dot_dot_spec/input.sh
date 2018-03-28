mkdir -p /tmp/cd_test/dir1/dir2
cd /tmp/cd_test/dir1/dir2
pwd
cd ..
pwd | sed 's;/private;;'

# cleanup
cd /
rm -rf /tmp/cd_test
