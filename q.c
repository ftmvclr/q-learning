#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const double gamma = 0.95; // curiosity coefficient
double epsilon = 0.8; // epsilon-greedy thing exploration vs exploitation
double omEpsilon = 0.2; // One Minus Epsilon
const double alpha = 0.1; // learning coefficient

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
	// !!!!!! call stateupdater thing with truck1
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
/*returns the address for where the movement based actions lead*/
double *landNext(int row, int col, int loaded, Action action){
	if(action == LEFT)
		return &state[row * 10 + col - 1][loaded][LEFT];
	else if(action == RIGHT)
		return &state[row * 10 + col + 1][loaded][RIGHT];
	else if(action == UP)
		return &state[(row + 1) * 10 + col][loaded][UP];
	else if(action == DOWN){
		return &state[(row - 1) * 10 + col][loaded][DOWN];
	}
	else
		return NULL;
	// TODO handle out of bounds!!
}

/*checks the coordinates and returns bool whether we are at load or no*/
int atLoadPosition(){
	return 0; // dummy
}

int atUnloadPosition(){
	return 0; // dummy
}

void updateParticularState(AgentPtr truck, Action action){
	int row = truck->locRow;
	int col = truck->locCol;
	int loaded = truck->loaded;
	double reward = judge(row, col, loaded);
	double *cur = &state[row * 10 + col][loaded][action];
	double *landing = cur;

	if(action != LOAD && action != UNLOAD) // moving
		landing = landNext(row, col, loaded, action);
	else if(action == LOAD && atLoadPosition() && loaded == 0){ // not loaded already
		landing = &state[row * 10 + col][1][LOAD];
		loaded = 1;
		// if it were to be already loaded it doesn't matter for it to re-load
	}
	else if(action == UNLOAD && atUnloadPosition() && loaded == 1){ // winning move btw
		loaded = 0;
		landing = &state[row * 10 + col][0][UNLOAD];
	}
	else{ // invalid load & unload. doesn't matter doesn't count as steps even
		// idk we gotta do something here?
	}
	*cur = *cur + alpha * (reward + gamma * *landing - *cur);

	// make sure to update the truck struct's positions
	truck->loaded = loaded;
	// TODO row col, div mod 
}