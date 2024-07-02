#include "gnuplot_i.h"
#include "parameters.h"



void gnuplotGrid( int t ) {

    char file[50] = "grid-results_";
    char number[10];
    sprintf( number, "%d", t );
    strcat( file, number );
    strcat( file, ".dat" );
    /* --------------------- */
    char outputCommand[50] = "set output 'grid-results_";
    strcat( outputCommand, number );
    strcat( outputCommand, ".png'" );
    //---------------------------------
    char fileCommand[50] = "plot '";
    strcat( fileCommand, file );
    strcat( fileCommand, "' matrix with image" );
    //---------------------------------
    
    gnuplot_ctrl * h;
    h = gnuplot_init();
    gnuplot_cmd(h, "");
    gnuplot_cmd(h, "unset colorbox");
    gnuplot_cmd(h, "set autoscale fix");
    gnuplot_cmd(h, "set palette defined (0 'white', 1 'green', 2 'red')");
    gnuplot_cmd(h, "set tics scale 0 ");
    gnuplot_cmd(h, "unset cbtics");
    gnuplot_cmd(h, "set cblabel 'Score'");
    gnuplot_cmd(h, "set terminal pngcairo size 1000,1000 enhanced font 'Verdana,12'");
    /* gnuplot_cmd(h, "set output 'grid-results.png'"); */
    gnuplot_cmd( h, outputCommand );
    gnuplot_cmd(h, fileCommand );
}

void gnuplotPopulation() {

    gnuplot_ctrl * h;
    h = gnuplot_init();
    gnuplot_cmd(h, "set key outside");
    gnuplot_cmd(h, "set xlabel 'Time steps'");
    gnuplot_cmd(h, "set ylabel 'Total Population'");
    gnuplot_cmd(h, "set terminal pngcairo size 1500,900 enhanced font 'Verdana,12'");
    gnuplot_cmd(h, "set output 'populationDynamics.png'");
    gnuplot_cmd(h, "plot 'populationDynamics.dat' u 0:1 w l lw 2.3 lc rgb \"forest-green\" t 'Prey', '' u 0:2 w l lw 2.3 lc rgb \"orange\" t 'Predator'");
}

void gnuplotVariance() {

    gnuplot_ctrl * h;
    h = gnuplot_init();
    gnuplot_cmd(h, "unset key");
    gnuplot_cmd(h, "set xlabel 'Window size'");
    gnuplot_cmd(h, "set ylabel 'Coefficient of variation'");
    gnuplot_cmd(h, "set terminal pngcairo size 1500,900 enhanced font 'Verdana,12'");
    gnuplot_cmd(h, "set output 'varianceWindow.png'");
    gnuplot_cmd(h, "plot 'varianceWindow.dat' u 1:2 w p");
}

void gnuplotAutocorrelation() {

    gnuplot_ctrl * h;
    h = gnuplot_init();
    gnuplot_cmd(h, "unset key");
    gnuplot_cmd(h, "set xlabel 'Lag time (time steps)'");
    gnuplot_cmd(h, "set ylabel 'Autocorrelation'");
    gnuplot_cmd(h, "set terminal pngcairo size 1500,900 enhanced font 'Verdana,12'");
    gnuplot_cmd(h, "set output 'autocorrelation.png'");
    gnuplot_cmd(h, "plot 'autocorrelation.dat' u 1:2 t '', 1 with lines linecolor 'red' t ''");
}

void writeGridtoFile ( int **grid, int size, int t ) {

    char filename[50] = "grid-results_";
    char number[10];
    sprintf( number, "%d", t );
    strcat( filename, number );
    strcat( filename, ".dat" );
    FILE *file;
    file = fopen(filename, "w");
    if ( file == NULL ) {
	printf("\n\tError: File can not be opened!\n");
    }
    /* --------------------- */
    int i = 0;
    int j = 0;
    while ( i < size ) {
	j = 0;
	while ( j < size ) {
	    fprintf( file, " %d", grid[i][j] );
	    j++;
	}
	fprintf( file, "\n" );
	i++;
    }
    fprintf(file, "\n");
    fclose( file );
}

void writePopulationtoFile ( int population[2] ) {

    FILE *file;
    file = fopen("populationDynamics.dat", "a");
    if ( file == NULL ) {
	printf("\n\tError: File can not be opened!\n");
    }
    fprintf( file, "%d ", population[0] );
    fprintf( file, "%d ", population[1] );
    fprintf( file, "\n" );
    fclose( file );
}

void writePreyPopulationtoFile ( int population[2] ) {

    FILE *file;
    file = fopen("preyPopulationDynamics.dat", "a");
    if ( file == NULL ) {
	printf("\n\tError: File can not be opened!\n");
    }
    fprintf( file, "%d\n", population[0] );
    fclose( file );
}

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
