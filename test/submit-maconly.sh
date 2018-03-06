rm -f newfile
ls | sort
env | grep "PATH"
export FOO "BAr"
env | grep "FOO=BAr"
unset FOO
env | grep "FOO=BAr"
/bin/ls
ls | cat -e
ls -r | sort | cat -e
echo "Testing redirections," > /tmp/test.txt
cat /tmp/test.txt | grep "Testing redirections,"
echo "with multiple lines" >> /tmp/test.txt
cat /tmp/test.txt| grep "with multiple lines"
wc -c < /tmp/test.txt
cat -e << EOF
Roses are red
Violets are blue
All my base are belong to you
And so are you
EOF
cat -e << EOF >> /tmp/test.txt
Roses are red
Violets are blue
All my base are belong to you
And so are you
EOF
cat /tmp/test.txt
ls -1; touch newfile; ls -1
cat newfile
ls -1; touch newfile; ls -1
rm newfile
mkdir test1 ; cd test1 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
cd ..; rm -rf test1
rm fifi
cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < \
sorted_poem > better_poem; cd -; echo "I prefer turnips anyway" >> \
/tmp/better_poem; cat /tmp/better_poem
Roses are red
Violets are blue
All my base are belong to you
I love you
EOF
rm nosuchfile 2>&-
rm nosuchfile 2>&1 | cat -e
echo "No dollar character" 1>&2 | cat -e
rm -f newfile
ls -1; touch newfile; ls -1
rm -f newfile
sdf 2>&-
(
  (
    rm -f newfile
    ls | sort
    env | grep "PATH"
    export FOO "BAr"
    env | grep "FOO=BAr"
    unset FOO
    env | grep "FOO=BAr"
    /bin/ls
    ls | cat -e
    ls -r | sort | cat -e
    echo "Testing redirections," > /tmp/test.txt
    cat /tmp/test.txt | grep "Testing redirections,"
    echo "with multiple lines" >> /tmp/test.txt
    cat /tmp/test.txt| grep "with multiple lines"
    wc -c < /tmp/test.txt
  )
  cat /tmp/test.txt
  ls -1; touch newfile; ls -1
  cat newfile
  ls -1; touch newfile; ls -1
  rm newfile
  mkdir test1 ; cd test1 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
  cd ..; rm -rf test1
  rm fifi
  rm nosuchfile 2>&-
  rm nosuchfile 2>&1 | cat -e
  echo "No dollar character" 1>&2 | cat -e
  rm -f newfile
  ls -1; touch newfile; ls -1
  rm -f newfile
  sdf 2>&-
  exit 42
)
