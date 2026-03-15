#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double gamma; // curiosity coefficient
double epsilon; // epsilon-greedy thing exploration vs exploitation
double alpha; // learning coefficient

typedef enum {LEFT, RIGHT, UP, DOWN, LOAD, UNLOAD} Action;

typedef struct{ // current state of the truck
	short LocRow;
	short LocCol;
	short loaded;
}Agent, *AgentPtr;

double state[100][2][6] = 0.0; // 10x10 map, loaded vs unloaded (2), 6 actions

void updateParticularState();

int main(){
	// stop when converges.
	int minTrials = 1000;
	int trialCount = 0;
	int bool_converged = 0;
//	for(; trialCount <= minTrials && !bool_converged; trialCount++){}

}

void updateParticularState(){

}