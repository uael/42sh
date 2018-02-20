echo $(echo "a       b           c          def	ghi")
echo "$(echo \"a       b           c          def	ghi\")"
echo "a$(echo \"a       b           c          def	ghi\")b"
echo '$(echo "a       b           c          def	ghi")'
echo $(ls)
echo $(ls -lar) | grep -o bg.c
echo $(ls -lartR) | grep -o bg.c
echo oops$(ls -l) | grep -o oopstotal
echo $HOME$(ls -l) | grep -o ${HOME}total
