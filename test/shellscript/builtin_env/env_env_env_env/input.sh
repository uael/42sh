env myvar=aa env myvar=ab env | grep myvar
env myvar2=bb env myvar3=cc env | grep myvar | sort
env | grep myvar | sort
