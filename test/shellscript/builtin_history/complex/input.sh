echo ==== 1
history
history -n
history -r

echo ==== 2
history 4 0
history -n 4 0
history -r 4 0
history -nr 4 0

echo ==== 3
history 0 4
history -n 0 4
history -r 0 4
history -rn 0 4

echo ==== 4
history 100 -1
echo ==== 4.1
history -n 100 -1
echo ==== 4.2
history -r 100 -1
echo ==== 4.3
history -rn 100 -1

echo ==== 5
history -- -8 100
history -n -- -8 100
history -r -- -8 100
history -nr -- -8 100

echo ==== 6
history echo
history -n echo
history -r echo
history -rn echo

echo === 7
history 20 echo
history echo 20
