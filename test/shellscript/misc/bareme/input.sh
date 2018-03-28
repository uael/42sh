cd /tmp
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi

cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd -; echo "I prefer turnips anyway" >> /tmp/better_poem; cat /tmp/better_poem
Roses are red
Violets are blue
All my base are belong to you
I love you 
EOF

cd /
rm -rf /tmp/test
rm -f /tmp/sorted_poem
rm -f /tmp/better_poem
