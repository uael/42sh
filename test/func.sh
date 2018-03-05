function mc {
  if [[ "$1" == "ask" ]]; then
    echo "Did the brace work ?"
  else
    echo "Yop mc !"
  fi
}
mc
mc ask
function lol { echo $0 $1 $2 $3 $4 $5; }
lol s sj s dhsjd has hda sk ahd
mc () {
  if [[ "$1" == "ask" ]]; then
    echo "Did the brace work ?"
  else
    echo "Yop mc !"
  fi
}
mc
mc ask
lol (  ) { echo $1 $2 $3 $4 $5; }
lol s sj s dhsjd has hda sk ahd
mc () {
  inner () {
    if [[ "$1" == "run" ]]; then
      echo "Why ? I don't have to run"
    else
      echo "Yop mc !"
    fi
  }
  inner $1
}
mc
mc run

dupscope () {
  echo "dup me plzzzz";
  dupscope () {
    echo dupped;
  }
  dupscope
}
dupscope
dupscope
dupscope () (
  echo "dup me plzzzz2";
  dupscope () (
    echo dupped2;
  )
  dupscope
)
dupscope
dupscope
echo $LOL
function exportlol {
    export LOL=lol
}
exportlol
echo $LOL
LOL=
exportlol () (
    echo $LOL
    export LOL=lol
    echo $LOL
)
exportlol
echo $LOL
