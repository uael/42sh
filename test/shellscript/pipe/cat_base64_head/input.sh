echo "===== 1"
python -c 'print "A"*100000' > /tmp/pip_bareme_spec_file
echo "===== 2"
cat /tmp/pip_bareme_spec_file | base64|head -c 2 | wc
echo "===== 3"
python -c 'print "A"*200000' > /tmp/pip_bareme_spec_file
echo "===== 4"
cat /tmp/pip_bareme_spec_file | base64|head -c 2 | wc
echo "===== 5"

rm -f /tmp/pip_bareme_spec_file
