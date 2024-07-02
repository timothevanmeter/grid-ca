#include <math.h>

/* All the functions declared here are called upon AFTER the end */
/* of a simulation and are not to be called DURING the simulation. */
/* These functions help in processing the data generated during the */
/* simulations. */

double datafileMean( char *filename ) {
    
    int maxSize = 7;
    char buffer[maxSize];
    int sum = 0;
    int n = 0;
    double mean = 0;
    
    FILE* file;
    file = fopen( filename, "r" );
    if ( file == NULL ) {
      perror( "Failed: " );
      return 1;
    }
    while ( fgets( buffer, maxSize, file ))
    {
        // Remove trailing newline
        buffer[strcspn( buffer, "\n" )] = 0;
        /* printf("%s\n", buffer); */
	sum += strtof(buffer, NULL);
	n++;
	
    }    
    fclose( file );
    mean = sum / n;

    return mean;
}

double datafileVariance( char *filename, double mean ) {

    int maxSize = 7;
    char buffer[maxSize];
    double sum = 0.0;
    double n = 0.0;
    double tmp = 0.0;
    double variance = 0.0;
    
    FILE* file;
    file = fopen( filename, "r" );
    if ( file == NULL ) {
      perror( "Failed: " );
      return 1;
    }
    while ( fgets( buffer, maxSize, file ))
    {
        // Remove trailing newline
        buffer[strcspn( buffer, "\n" )] = 0;
        /* printf("%s\n", buffer); */
	tmp = strtof(buffer, NULL);
	sum += ( tmp - mean ) * ( tmp - mean );
	n++;
	
    }    
    fclose( file );
    variance = ( sum / n ) / mean;

    return variance;
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
