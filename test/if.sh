[[ -d . ]] && echo a || echo b

if [[ -d . ]]; then echo a; fi

if true; then echo a; else echo b; fi
if false; then echo true; elif false; then echo false; else echo foo; fi
if false; then echo true; elif true; then echo false; else echo foo; fi

if true; then
  echo a;
else
  echo b;
fi

if false; then
  echo true;
elif false; then
  echo false;
else
  echo foo;
fi

if false; then
  echo true;
elif true; then
  echo false;
else
  echo foo;
fi

if while false; do echo b; done; then echo a; fi
