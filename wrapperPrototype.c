#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define NUMBERPARAMETERS 2

int range ( int parameters[NUMBERPARAMETERS][3], int i ) {

    return (int)( ((parameters[i][1] - parameters[i][0]) / parameters[i][2])+1 );
}

int cumulRange ( int parameters[NUMBERPARAMETERS][3], int i ) {

    int cumul = 1;
    i++;
    while ( i < NUMBERPARAMETERS ) {
	cumul = cumul * range( parameters, i );
	i++;
    }
    return cumul;//( parameters[i][1] - parameters[i][0] + 1 ) / parameters[i][2];
}


int returnVal ( int parameters[NUMBERPARAMETERS][3], int parameter, int positionInRange ) {

    int val;
    val = parameters[parameter][0] + ( parameters[parameter][2] * positionInRange );
    return val;
    
}

int main () {


    // 2D array containing all the parameters values:
    //  min, max and step for each parameter.
    int parameters[NUMBERPARAMETERS][3] = { {0, 1, 1}, {0, 9, 3} };

    int cumul = 1;
    // Calculates the TOTAL cumulative range, but with a trick:
    //  since the cumulRange() function adds 1 to the second argument
    //  we need to pass -1 so it takes into account the very first
    //  parameter into account when making the calculation. 
    cumul = cumulRange( parameters, -1 );
    
    printf( " cumulative range = %d\n", cumul );

    // Unused variable:
    // int position = 0;
    int val = 0;
	
    for ( int i = 0; i < cumul; i++ ) {
	printf( " (%d) \t", i );
	for ( int j = 0; j < NUMBERPARAMETERS; j++ ) {

	    // Returns the position of the value to use within the
	    //  range of the parameter for a given parameter and
	    //  iteration or simulation number.
	    //  cumulRange() calculates the cumulative range for all
	    //   parameters after position j and
	    //   range() calculates the range of parameter j itself.
	    int position = (int)( i / cumulRange( parameters, j ) % range( parameters, j ));
	    val = returnVal( parameters, j, position );	
	    printf( "%d ", val );
	}
	printf( "\n" );
    }
    
    return 0;
}
