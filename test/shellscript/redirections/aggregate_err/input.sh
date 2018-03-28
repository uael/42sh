touch /tmp/dummy_file
(echo abc 5< /tmp/dummy_file; cat /tmp/dummy_file)
(echo abc 5<& /tmp/dummy_file; cat /tmp/dummy_file)
(echo abc 5> /tmp/dummy_file; cat /tmp/dummy_file)
(echo abc 5>& /tmp/dummy_file; cat /tmp/dummy_file)
(echo abc 5>> /tmp/dummy_file; cat /tmp/dummy_file)

# cleanup
rm -r /tmp/dummy_file
