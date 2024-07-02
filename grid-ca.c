#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "grid-ca.h"
#include "parameters.h"


// The two integers keep track of the total number
//  of predators and preys in the simulation environment
//  at each time step. These two variables need to be
//  accessible by every functions and files.
extern int population[2] = { 0, 0 };


int main() {

    /* printf( "\n\n\n" ); */
    int extinction = RUNTIME;
    
    // INITIALISATION
    //  Initialises the random number with a seed and
    //   declares the grid object which will be used
    //   by other functions and files.
    srand(time(NULL));
    int *grid[SIZE];

    // Initialises the grid with a random configuration
    //  of preddators, preys and empty space.
    initialiseSimulation( grid, population );

    // Starts the simulation for as many time steps as
    //  the RUNTIME parameter's value.
    extinction = runSimulation( grid, population );

    // Command to produce an image of the simulation grid
    //  for every interval of the RECORDINGRATE parameter.
    if ( GRAPHGRID == 1 ){
	graphGridresults( extinction );
    }

    // Command to produce an image of the population's
    //  dynamics of predator and prey for the whole
    //  duration of the simulation.
    graphPopulationDynamics();

    // Measures the variance of the prey population's time
    //  serie within a fixed window comprising a certain
    //  proportion of the environment corresponding to the
    //  WINDOWSIZE parameter's value.
    if ( extinction > 2000 && MEASUREVARIANCE == 1 ) {
	measureVariance();
    }

    if ( extinction > 2000 && MEASUREVARIANCE == 1 && MEASUREAUTOCORRELATION == 1 ) {
      measureAutocorrelation();
    }
    
    //system( "cat *.png | ffmpeg -f image2pipe -i - output.mp4" );
    
    /* printf( "\n\n\n" ); */
	
    return 0;
}
