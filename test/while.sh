i=1; while [[ $i -ne 43 ]]; do echo $i; i=$(( $i + `echo $(echo 1)` )); done
i=1;
while [[ $i -ne 43 ]]; do
  echo $i;
  i=$(( $i + `echo $(echo 1)` ));
done
i=1
while [[ $i -ne 43 ]]
do
  echo $i
  i=$(( $i + `echo $(echo 1)` ))
done
i=1
while [[ $i -ne 43 ]];
do
  echo $i;
  i=$(( $i + `echo $(echo 1)` ));
done
