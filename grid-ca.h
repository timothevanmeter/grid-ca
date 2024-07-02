#include "parameters.h"
#include "randomUtils.h"
#include "utils.h"
#include "analysis.h"

void graphPopulationDynamics () {
    
    gnuplotPopulation();
}

void measureVariance () {

    int i = MINWINDOWSIZE;
    while ( i < MAXWINDOWSIZE ) {

	char file[50] = "totalPreyWindow";
	char number[10] = "";
	sprintf( number, "%d", i );
	strcat( file, number );
	strcat( file, ".dat" );
	double mean = datafileMean( file );
	double variance = datafileVariance( file, mean );

	//~~~~~~~~~~~~~
	// Attempt to normalise the variance by the window size:
	variance = variance / i;
	//~~~~~~~~~~~~~

	// Write to file without carriage return
	writeInttoFile( "varianceWindow.dat", i, 0 );
	// Write to file with carriage return
	writeDoubletoFile( "varianceWindow.dat", variance, 1 );
	i++;
    }
    gnuplotVariance();
}

void measureAutocorrelation () {

    double mean = 0.0;
    double variance = 0.0;
    double result = 0.0;
    mean = datafileMean( "preyPopulationDynamics.dat" );
    variance = datafileVariance( "preyPopulationDynamics.dat", mean );

    // To compute autocorrelation for multiple lag values:
    for ( int i = 1; i < 500; i++ ) {

	result = datafileAutoCorrelation( "preyPopulationDynamics.dat", i, mean, variance );
	/* printf( "\n\t lag = %d\n", i ); */
	/* printf( "%d %.1f\n", i, result ); */
	writeInttoFile( "autocorrelation.dat", i, 0 );
	writeDoubletoFile( "autocorrelation.dat", result, 1 );
	//i += 1;
    }

    /* int i = MINWINDOWSIZE; */
    /* while ( i < MAXWINDOWSIZE ) { */

    /* 	char file[50] = "totalPreyWindow"; */
    /* 	char number[10] = ""; */
    /* 	sprintf( number, "%d", i ); */
    /* 	strcat( file, number ); */
    /* 	strcat( file, ".dat" ); */
    /* 	double mean = datafileMean( file ); */
    /* 	double variance = datafileVariance( file, mean ); */

    /* 	//~~~~~~~~~~~~~ */
    /* 	// Attempt to normalise the variance by the window size: */
    /* 	variance = variance / i; */
    /* 	//~~~~~~~~~~~~~ */

    /* 	// Write to file without carriage return */
    /* 	writeInttoFile( "varianceWindow.dat", i, 0 ); */
    /* 	// Write to file with carriage return */
    /* 	writeDoubletoFile( "varianceWindow.dat", variance, 1 ); */
    /* 	i++; */
    /* } */
    
    gnuplotAutocorrelation();
}

/* void recordWindow( int t, int number, int **grid, int iOrigin, int jOrigin, int sizeWindow ) { */

/*     if ( t > 500 ) { */

/* 	int i = MINWINDOWSIZE; */
/* 	while ( i < MAXWINDOWSIZE ) { */
/* 	    char file[50] = "totalPreyWindow"; */
/* 	    char number[10] = ""; */
/* 	    sprintf( number, "%d", i ); */
/* 	    strcat( file, number ); */
/* 	    strcat( file, ".dat" ); */
/* 	    writeInttoFile( file, totalPreyWindow( grid, iOrigin, jOrigin, i ), 1 ); */
/* 	    i++; */
/* 	} */
/*     } */
/* } */


int totalPreyWindow ( int **grid, int iOrigin, int jOrigin, int sizeWindow ) {
    int i = iOrigin;
    int j = jOrigin;
    int totalPrey = 0;
    while ( ( i < iOrigin + sizeWindow ) && i < SIZE ) {
	j = jOrigin;
	while ( ( j < jOrigin + sizeWindow ) && j < SIZE ) {
	    if ( grid[i][j] == 1 ) {
		totalPrey++;
	    }
	    j++;
	}
	i++;
    }
    return totalPrey;
}

/* void generateGridTest ( int **grid, int size, int population[2] ) { */

/*     int i = 0; */
/*     int j = 0; */
/*     while ( i < size ) { */
/* 	j = 0; */
/* 	while ( j < size ) { */
/* 	    if ( i == 0 && j == 0 ) { */
/* 		grid[i][j] = 1; */
/* 		population[0]++; */
/* 	    } */
/* 	    else if ( i == size-1 && j == size-1 ) { */
/* 		grid[i][j] = 2; */
/* 		population[1]++; */
/* 	    } */
/* 	    else { */
/* 		grid[i][j] = 0; */
/* 	    } */
/* 	    j++; */
/* 	} */
/* 	i++; */
/*     } */
/* } */

void generateGridRandom ( int **grid, int size, int population[2] ) {

    int i = 0;
    int j = 0;
    int test = 0;
    while ( i < size ) {
	/* printf( " %d\n", i ); */
	j = 0;
	while ( j < size ) {

	    test = rand() % 100;
	    if ( test < AGENTSDENSITY ) {

		// We create a new random number so there is
		//  no correlation between the successful generation
		//  of an agent and one type of agent, thus over-
		//  representing them on the lattice.
		test = rand() % 100;
		if ( test < PREYRATIO ) {
		    grid[i][j] = 1;
		    population[0]++;
		}
		else {
		    grid[i][j] = 2;
		    population[1]++;
		}
	    }
	    else {
		grid[i][j] = 0;
	    }
	    j++;
	}
	i++;
    }
}



int checkExtinction ( int population[2] ) {

    if( population[0] == 0 || population[1] == 0 ) {
	return 1;
    }
    else {
	return 0;
    }
}

int updatePrey ( int **grid, int population[2], int updated[LENGTH], int i , int j ) {

    if ( randomNum() > ( 1.0 - GROWTH ) ) {
	for ( long int k = -1; k < 2; k++ ) {
	    if ( i+k < SIZE && i+k >= 0 ) {
		for ( long int l = -1; l < 2; l++ ) { 
		    if ( j+l < SIZE && j+l >= 0 ) {
			if ( grid[i+k][j+l] == 0 ) {

			    // A new prey is born on this cell
			    grid[i+k][j+l] = 1;
			    int tmp = ( (i+k) * SIZE ) + j+l;
			    updated[tmp] = 1;			    
			    population[0]++;
			    return 0;
			}
		    }
		}
	    }
	}
    }
    return 0;
}

int reproductionPredator ( int **grid, int population[2], int updated[LENGTH], int i, int j ) {

    for ( long int k = -1; k < 2; k++ ) {
	if ( i+k < SIZE && i+k >= 0 ) {
	    for ( long int l = -1; l < 2; l++ ) {
		if ( j+l < SIZE && j+l >= 0 ) {
		    if ( grid[i+k][j+l] == 0 ) {

			// A new predator is born on this cell
			grid[i+k][j+l] = 2;
			int tmp = ( (i+k) * SIZE ) + j+l;
			updated[tmp] = 1;
			// The total count is updated for the
			//  predator population
			/* printf(" +1 Predator\n"); */
			population[1]++;
			return 0;
		    }
		}
	    }
	}
    }
    return 0;
}

int updatePredator ( int **grid, int population[2], int updated[LENGTH], int i , int j ) {

    // Background mortality of predators
    if ( randomNum() > ( 1.0 - MORTALITY ) ) {
	// Removal of predator on the grid
	grid[i][j] = 0;
	// And in the total count
	/* printf(" -1 Predator\n"); */
	population[1]--;
	return 0;
    }
    if ( randomNum() > ( 1.0 - ATTACK ) ) {
	for ( long int k = -1; k < 2; k++ ) {
	    if ( i+k < SIZE && i+k >= 0 ) {
		for ( long int l = -1; l < 2; l++ ) {
		    if ( j+l < SIZE && j+l >= 0 ) {
			if ( grid[i+k][j+l] == 1 ) {

			    // Successful attack of predator on prey
			    // Removal of prey on the grid
			    grid[i+k][j+l] = 0;
			    // And in the total count
			    /* printf(" -1 Prey\n"); */
			    population[0]--;
			    // The predator is allowed to reproduce after a
			    //  successful predation event
			    reproductionPredator( grid, population, updated, i+k, j+l );
			    return 0;
			}
		    }
		}
	    }
	    
	}
    }
    return 0;
}

void generateFYShuffle( int order[LENGTH] ) {
    //implementation of Fisher Yates shuffling algorithm
    int i, j, tmp; // create local variables to hold values for shuffle
    i = 0;
    while ( i < LENGTH ) {
	order[i] = i;
	i++;
    }
    for (i = LENGTH - 1; i > 0; i--) { // for loop to shuffle
	j = rand() % (i + 1); //randomise j for shuffle with Fisher Yates
	tmp = order[j];
	order[j] = order[i];
	order[i] = tmp;
    }
}


int updateGridRandom ( int **grid, int size, int population[2] ) {

    int i = 0;
    int line = 0;
    int col = 0;
    int *order = malloc( (SIZE * SIZE) * sizeof( int ) );
    int *updated = malloc( (SIZE * SIZE) * sizeof( int ) );
    generateFYShuffle( order );
    /* printf("order : \n"); */
    for ( i = 0; i < LENGTH; i++ ) {
	updated[i] = 0;
	/* printf(" %d ", order[i]); */
    }
    /* printf("\n"); */
    
    for ( i = 0; i < LENGTH; i++ ) {

	if ( updated[ order[i] ] == 0 ) {
	    line = (int)( order[i] / SIZE );
	    col = order[i] % SIZE;
	    if( grid[line][col] == 1 ){
		updatePrey( grid, population, updated, line, col );
	    }
	    else if ( grid[line][col] == 2 ){
		updatePredator( grid, population, updated, line, col );
	    }
	}
    }
    free( order );
    free( updated );
    return 0;
}


// ----------------------------------------------------------------
// ----------------------------------------------------------------

int runSimulation ( int **grid, int population[2] ) {

    int t = 0;
    /* int i = 2; */
    while( t < RUNTIME ) {

	if( RECORDGRID != 0 ) {
	    if( (t % RECORDINGRATE) == 0 && GRAPHGRID == 1 ){
		writeGridtoFile( grid, SIZE, t );
	    }
	}
	writePopulationtoFile( population );
	// Creating a file only for the prey population:
	writePreyPopulationtoFile( population );
	if( checkExtinction( population ) != 0 ) {
	    return t;
	}

	// MEASURE VARIANCE HERE !!!
	if ( MEASUREVARIANCE == 1 ) {

	    /* recordWindow(); */
	    if ( t > 2000 ) {

		int i = MINWINDOWSIZE;
		while ( i < MAXWINDOWSIZE ) {
		    char file[50] = "totalPreyWindow";
		    char number[10] = "";
		    sprintf( number, "%d", i );
		    strcat( file, number );
		    strcat( file, ".dat" );
		    writeInttoFile( file, totalPreyWindow( grid, 0, 0, i ), 1 );
		    i++;
		}
	    }
	}
	
	/* updateGrid( grid, SIZE, population ); */
	updateGridRandom ( grid, SIZE, population );
	t++;
    }
    return RUNTIME;
}

int ** initialiseSimulation ( int **grid, int population[2] ) {

    int i = 0;
    while ( i < SIZE ) {

	grid[i] = malloc( SIZE * sizeof( int ) );
	i++;
    }
    generateGridRandom( grid, SIZE, population );
    /* generateGridTest( grid, SIZE, population ); */
    writePopulationtoFile( population );
    return grid;
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

void graphGridresults ( int extinction ) {

    int t = 0;
    int limit;
    if ( extinction < RUNTIME ) {
	limit = extinction;
    }
    else {
	limit = RUNTIME;
    }
    while( t < limit ) {
	if( t % RECORDINGRATE == 0 && GRAPHGRID == 1 ){
	    gnuplotGrid( t );
	}
	t++;
    }
}
