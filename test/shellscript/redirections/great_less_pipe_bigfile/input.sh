man tar > /tmp/bigfile
man tar >> /tmp/bigfile
man tar >> /tmp/bigfile
man tar >> /tmp/bigfile
cat < /tmp/bigfile | wc

# cleanup
rm -f /tmp/bigfile
