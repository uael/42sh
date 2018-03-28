2>/dev/null unset OLDPWD || unsetenv OLDPWD
cd -- -

2>/dev/null OLDPWD=toto || setenv OLDPWD toto
cd -- -
