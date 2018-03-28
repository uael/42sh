# /tmp
#   - tmp_sym -> /tmp
#   - test01
#      - tmp_sym -> /tmp
#      - test01_sym -> test01
#   - test01_sym
#   - test02
#     - test01_sym

mkdir /tmp/test01
mkdir /tmp/test02
ln -s /tmp /tmp/tmp_sym
ln -s /tmp /tmp/test01/tmp_sym
ln -s /tmp/test01 /tmp/test02/test01_sym
ln -s /tmp/test01 /tmp/test01/test01_sym
ln -s /tmp/test01 /tmp/test01_sym
cd /tmp
pwd
cd tmp_sym
pwd
cd test01
pwd
cd tmp_sym
pwd
cd test01_sym
pwd
cd test01_sym
pwd
cd tmp_sym
pwd
cd test02
pwd
cd test01_sym
pwd
cd tmp_sym
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd ..
pwd
cd test01/tmp_sym/test01_sym/../test02/test01_sym/../../../tmp_sym
pwd
cd ../../../
pwd

# Physical resolution

cd /tmp/test01/tmp_sym/test01_sym/test01_sym/tmp_sym/test02/test01_sym/tmp_sym
pwd
cd -P test01
pwd
cd -P /tmp/test01/tmp_sym/test01_sym/test01_sym/tmp_sym/test02/test01_sym/tmp_sym
pwd

# Try to go back too far

cd ../../../../../../../../../
pwd
cd ..
cd ..
cd ..
cd ..
pwd

# Simplify path

cd /tmp/../../../../tmp/test01/./././test01_sym/./././test01_sym/tmp_sym/test02/test01_sym/test01_sym/.././././.././././test01_sym/.././../../tmp_sym/test01/../././.././tmp_sym/../tmp_sym/../tmp_sym/../tmp_sym/tmp_sym/tmp_sym/../../../.././././.
pwd

# Many slashes

cd .//////////////..////////../././///./////././../////../../../../tmp/////.////.////////..////tmp///////////////test01/.///////////..////////////..///////////../////////////../////////././///tmp/.///////////
pwd
cd /////////////
pwd

#cleanup
rm -rf /tmp/tmp_sym
rm -rf /tmp/test01
rm -rf /tmp/test02
rm -rf /tmp/test01_sym
