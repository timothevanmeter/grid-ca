#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "analysis.h"

void writeInttoFile ( char *filename, int num, int newline ) {

    FILE *file;
    file = fopen( filename, "a" );
    if ( file == NULL ) {
	printf("\n\tError: File can not be opened!\n");
    }
    if ( newline == 1 ) {
	fprintf( file, "%d\n", num );
    }
    else if ( newline == 0 ) {
	fprintf( file, "%d ", num );
    }
    fclose( file );
}

void writeDoubletoFile ( char *filename, double num, int newline ) {

    FILE *file;
    file = fopen( filename, "a" );
    if ( file == NULL ) {
	printf("\n\tError: File can not be opened!\n");
    }
    if ( newline == 1 ) {
	fprintf( file, "%.2f\n", num );
    }
    else if ( newline == 0 ) {
	fprintf( file, "%.2f ", num );
    }
    fclose( file );
}

double datafileAutoCorrelation( char *filename, int lag, double mean, double variance ) {

    int maxSize = 7;
    char bufferLag[maxSize];
    char bufferNolag[maxSize];
    double sum = 0.0;
    // n is declared as a double to avoid problem when it
    //  is used with other doubles in a operation.
    double n = 0.0;
    double tmpLag = 0.0;
    double tmpNolag = 0.0;    
    double AutoCorr = 0.0;
    
    FILE* fileLag;
    FILE* fileNolag;
    fileNolag = fopen( filename, "r" );
    if ( fileNolag == NULL ) {
      perror( "Failed: " );
      return 1;
    }
    fileLag = fopen( filename, "r" );
    if ( fileLag == NULL ) {
      perror( "Failed: " );
      return 1;
    }
    
    while ( fgets( bufferLag, maxSize, fileLag ))
    {
	if ( n >= lag ) {
	    fgets( bufferNolag, maxSize, fileNolag );
	    // Remove trailing newline
	    bufferLag[strcspn( bufferLag, "\n" )] = 0;
	    bufferNolag[strcspn( bufferNolag, "\n" )] = 0;
	    /* printf("%s\t", bufferNolag); */
	    /* printf("%s\n", bufferLag); */
	    tmpLag = strtof(bufferLag, NULL);
	    tmpNolag = strtof(bufferNolag, NULL);
	    sum += ( tmpLag - mean ) * ( tmpNolag - mean );
	}
	n++;
	
    }
    fclose( fileNolag );
    fclose( fileLag );
    AutoCorr = sum / ( variance * n );

    return AutoCorr;
}



int main() {

    double mean = 0.0;
    double variance = 0.0;
    double result = 0.0;
    /* int lag = 1; */

    mean = datafileMean( "preyPopulationDynamics.dat" );
    variance = datafileVariance( "preyPopulationDynamics.dat", mean );

    // Version for a single run over a file with one lag value:
    /* result = datafileAutoCorrelation( "test.dat", i, mean, variance ); */
    /* printf( "\n\n\t mean = %.1f\n", mean ); */
    /* printf( "\t deviation = %.1f\n", variance * 100 ); */
    /* printf( "\t lag = %d\n", lag );     */
    /* printf( "\n\t autocorrelation = %.1f\n\n", result ); */

    // To compute autocorrelation for multiple lag values:
    printf( "\n\n\n" );
    for ( int i = 1; i < 500; i++ ) {

	result = datafileAutoCorrelation( "preyPopulationDynamics.dat", i, mean, variance );
	/* printf( "\n\t lag = %d\n", i ); */
	/* printf( "%d %.1f\n", i, result ); */
	writeInttoFile( "autocorr.dat", i, 0 );
	writeDoubletoFile( "autocorr.dat", result, 1 );
	//i += 1;
    }
    printf( "\n\n" );
    
    return 0;
}
