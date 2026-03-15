#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double gamma; // curiosity coefficient
double epsilon; // epsilon-greedy thing exploration vs exploitation
double alpha; // learning coefficient

typedef enum {LEFT, RIGHT, UP, DOWN, LOAD, UNLOAD} Action;

typedef struct{ // current state of the truck
	short locRow;
	short locCol;
	short loaded;
}Agent, *AgentPtr;

double state[100][2][6] = {0.0}; // 10x10 map, loaded vs unloaded (2), 6 actions

void updateParticularState(AgentPtr truck, Action action);

int main(){
	// stop when converges.
	AgentPtr truck1 = calloc(1, sizeof(Agent));
	int minTrials = 1000;
	int trialCount = 0;
	int bool_converged = 0;
//	for(; trialCount <= minTrials && !bool_converged; trialCount++){}

}

void updateParticularState(AgentPtr truck, Action action){ // technically we update where the agent is at don't we?
	state[truck->locRow * 10 + truck->locCol][truck->loaded][action]; // TODO
}