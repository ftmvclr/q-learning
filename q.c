#include <stdio.h>

double gamma; // curiosity coefficient
double epsilon; // epsilon-greedy thing
double alpha; // learning coefficient

enum actions {LEFT, RIGHT, UP, DOWN, LOAD, UNLOAD};
typedef enum actions Action;

typedef struct{
	int row;
	int col;
}State, *StatePtr;

void updateParticularState(State s, Action a);

int main(){

}

void updateParticularState(State s, Action a){

}