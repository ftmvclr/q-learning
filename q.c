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

typedef struct objectToPickup{
	short locRow;
	short locCol;
}PickupCoords;

typedef struct placeToUnload{
	short locRow;
	short locCol;
}UnloadCoords;


double state[100][2][6] = {0.0}; // 10x10 map, loaded vs unloaded (2), 6 actions

void updateParticularState(AgentPtr truck, Action action);

int main(){
	// stop when converges.
	AgentPtr truck1 = calloc(1, sizeof(Agent));
	int minTrials = 1000;
	int trialCount = 0;
	int bool_converged = 0;
//	for(; trialCount <= minTrials && !bool_converged; trialCount++){
//		while(){ // continue until loaded successfully
//			first take an action
//			idk how to implement reward thing yet
//			then update that state
//			if action = not load or unload(less than 4 or smth) steps++
// 	    }
// 	    if less than mintrial don't send to "did it converge?" function
//	    else do send it, check return value
// }
}
double judge(int row, int col, int loaded){
	return 0; // dummy
}

double *landNext(int row, int col, Action action){
	if(action == LEFT)
		return &state[row * 10 + col - 1];
	else if(action == RIGHT)
		return &state[row * 10 + col + 1];
	else if(action == UP)
		return &state[(row + 1) * 10 + col];
	else if(action == DOWN){
		return &state[(row - 1) * 10 + col];
	}
	else
		return NULL;
	// TODO handle out of bounds!!
}

void updateParticularState(AgentPtr truck, Action action){ // technically we update where the agent is at don't we?
	int row = truck->locRow;
	int col = truck->locCol;
	int loaded = truck->loaded;
	double reward = judge(row, col, loaded);
	double *landing = NULL;

	double *cur = &state[row * 10 + col][loaded][action];
	if(action != LOAD && action != UNLOAD)
		landing = landNext(row, col, action);
	*cur = *cur + alpha * (reward + gamma * landing[loaded][action]); // fix the syntax


	// calculate where that action lands us at and then also make sure to update the truck struct's positions
}