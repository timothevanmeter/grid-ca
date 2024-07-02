#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


char * add_zeroes( char * s, int t ) {

  if( t == 0 ) {
    return s;
  }
  else {
    char * zero = "0";
    char number[10];
    sprintf( number, "%d", t );
    strcat( zero, number );
    return add_zeroes( strcat( s, zero ), t - 1 );
  }
}


int main() {

  char * s = malloc( 10 * sizeof(char) );
  
  for ( int i = 0; i < 10; i++ ) {

    printf( "%s", add_zeroes( s, i ) );
  }
  free( s );

  return 0;
}
