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
