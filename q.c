#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef enum {LEFT, RIGHT, UP, DOWN, LOAD, UNLOAD} Action;
const double gamma = 0.95; // curiosity coefficient
double epsilon = 0.8; // epsilon-greedy thing exploration vs exploitation
/*picked final epsilon to be 0.1 approximately 0.014 decay at each 100 steps*/
const double alpha = 0.1; // learning coefficient

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

PickupCoords obj = {4, 0};
UnloadCoords plc = {9, 9};

double state[100][2][6] = {0.0}; // 10x10 map, loaded vs unloaded (2), 6 actions
int trialSteps[5000] = {0};
Action takeAction(AgentPtr truck);
int atLoadPosition(int row, int col);
int atUnloadPosition(int row, int col);
int updateParticularState(AgentPtr truck, Action action);
double *landNext(int row, int col, int loaded, Action action, AgentPtr truck);

int main(){
	srand(time(NULL));
	// stop when converges.
	AgentPtr truck1 = calloc(1, sizeof(Agent));
	if(truck1 == NULL)
		return 1;
	truck1->locRow = 0; truck1->locCol = 9;
	Action tempAct = -1;
	int minTrials = 1000;
	int trialCount = 0;
	int bool_converged = 0;
	int steps = 0;
	int bool_won = 0;
	while(trialCount < 5000){
		steps = 0;
		truck1->locCol = 9; truck1->locRow = 0; truck1->loaded = 0;
		while(1){ // continue until loaded successfully
			tempAct = takeAction(truck1);
			bool_won = updateParticularState(truck1, tempAct);
			if(tempAct != LOAD && tempAct != UNLOAD)
				steps++;
			if(bool_won)
				break;
		}
		trialSteps[trialCount++] = steps;
		if(trialCount % 100 == 0){
			epsilon -= 0.014;
		}
	}
	// TODO we are supposed to decay the epsilon over time!!
	free(truck1);
}

Action takeAction(AgentPtr truck){
	double r = (double)rand() / RAND_MAX;
	Action action = -1;
	int row, col, loaded = 0;
	double best = 0.0;
	row = truck->locRow; col = truck->locCol; loaded = truck->loaded;
	if(r < epsilon) {
		action = rand() % 6;
	}
	else { // take the best action at this position TODO
		double *q_wo_action = state[row * 10 + col][loaded]; // q  wihtout action
		best = q_wo_action[0]; action = 0;
		for(int i = 1; i < 6; i++){
			if(q_wo_action[i] > best){
				action = i;
				best = q_wo_action[i];
			}
		}
	}
	return action;
}

/*returns the address for where the movement based actions lead*/
double *landNext(int row, int col, int loaded, Action action, AgentPtr truck){
	if(action == LEFT && col != 0){
		truck->locCol = col - 1;
		return &state[row * 10 + col - 1][loaded][LEFT];
	}
	else if(action == RIGHT && col != 9){
		truck->locCol = col + 1;
		return &state[row * 10 + col + 1][loaded][RIGHT];
	}
	else if(action == UP && row != 0){
		truck->locRow = row - 1;
		return &state[(row - 1) * 10 + col][loaded][UP];
	}	
	else if(action == DOWN && row != 9){
		truck->locRow = row + 1;
		return &state[(row + 1) * 10 + col][loaded][DOWN];
	}
	else{ // out of bounds, stay where you are
		return NULL;
	}
}

int updateParticularState(AgentPtr truck, Action action){
	int row = truck->locRow;
	int col = truck->locCol;
	int loaded = truck->loaded;
	double reward;
	double *cur = &state[row * 10 + col][loaded][action];
	double *landing = cur;

	if(action != LOAD && action != UNLOAD){// moving
		landing = landNext(row, col, loaded, action, truck);
		if(landing == NULL){
			reward = -100;
			landing = cur;
		}
		else
			reward = -1;
	}
	else if(action == LOAD && atLoadPosition(row, col) && loaded == 0){
		landing = &state[row * 10 + col][1][LOAD];
		loaded = 1;
		reward = 50;
		// if it were to be already loaded it doesn't matter for it to re-load
	}
	else if(action == UNLOAD && atUnloadPosition(row, col) && loaded == 1){ // winning move btw
		loaded = 0;
		landing = &state[row * 10 + col][0][UNLOAD];
		reward = 1000;
		*cur = *cur + alpha * (reward + gamma * *landing - *cur);
		truck->loaded = 0;
		return 1;
	}
	else{ // invalid load & unload.
		reward = -50;
	}
	// !! truck got updated up until this point
	double bestNext = state[truck->locRow * 10 + truck->locCol][truck->loaded][0];;
	for(int i = 0; i < 6; i++){ 
		if(state[truck->locRow * 10 + truck->locCol][truck->loaded][i] > bestNext)
			bestNext = state[truck->locRow * 10 + truck->locCol][truck->loaded][i];
	}
	*cur = *cur + alpha * (reward + gamma * bestNext - *cur);
	truck->loaded = loaded;
	return 0;
}

/*checks the coordinates and returns bool whether we are at load or no*/
int atLoadPosition(int row, int col){
	return (row == obj.locRow && col == obj.locCol);
}

int atUnloadPosition(int row, int col){
	return (row == plc.locRow && col == plc.locCol); // dummy
}