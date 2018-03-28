  true && true   || echo 1
( true && true ) || echo 2

  true && false   || echo 3
( true && false ) || echo 4

  false && true   || echo 5
( false && true ) || echo 6

  false && false   || echo 7
( false && false ) || echo 8

true ||   true && echo 9 
true || ( true && echo 10 )

true ||   false && echo 11  
true || ( false && echo 12 )

false ||   true && echo 13  
false || ( true && echo 14 )

false ||   false && echo 15  
false || ( false && echo 16 )
