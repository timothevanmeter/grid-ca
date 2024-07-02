
// MODEL PARAMETERS
#define SIZE 200
#define LENGTH (SIZE*SIZE)
#define RUNTIME 100
#define PREYRATIO 40     //   #prey / #totalagents 
#define AGENTSDENSITY 30 //   (#agents / #cells)*100

// AGENT'S PARAMETERS
#define GROWTH 0.22
#define ATTACK 0.14
#define MORTALITY 0.06

// OUTPUT PARAMETERS
// Set the parameter below to 0 to
//  avoid generating data.
#define RECORDGRID 1
#define RECORDINGRATE 1
// Boolean controlling if the grid should
//  be graphed in the results.
#define GRAPHGRID 1

// Measurement of the population's
//  dynamics variance within a window
//  in the simulation environment.
#define MEASUREVARIANCE 0
#define MEASUREAUTOCORRELATION 0
#define MAXWINDOWSIZE 120
#define MINWINDOWSIZE 2
