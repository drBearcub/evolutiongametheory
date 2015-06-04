#include <iostream>
#include <stdlib.h>     
#include <time.h>      
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class animalType{
public:
	int type;
	animalType* beatOne;
	animalType* beatTwo;
		/* 0 - rock,
		 * 1 - paper,
		 * 2 - scissors,
		 * 3 - lizzard,
		 * 4 - spock,
		 */
};

vector <animalType*> types;
vector <animalType*> population;
ofstream myfile;

void initialize(){
	for(int i = 0; i < 5; ++i) {
		animalType* a = new animalType;
		a->type = i;
		types.push_back(a);
	}
	types[0]->beatOne = types[2];
	types[0]->beatTwo = types[3];
	types[1]->beatOne = types[0];
	types[1]->beatTwo = types[4];
	types[2]->beatOne = types[3];
	types[2]->beatTwo = types[1];
	types[3]->beatOne = types[1];
	types[3]->beatTwo = types[4];
	types[4]->beatOne = types[0];
	types[4]->beatTwo = types[2];
}

void generatePopulation(int size){
	while(size--) {
		population.push_back(types[rand()%5]);
	}
}

void generatePopulation(int rock, int scissors, int paper, int lizzard, int spock){
	while(rock--){
		population.push_back(types[0]);
	}
	while(paper--){
		population.insert(population.begin() + rand() % population.size() , types[1]);
	}
	while(scissors--){
		population.insert(population.begin() + rand() % population.size() , types[2]);
	}
	while(lizzard--){
		population.insert(population.begin() + rand() % population.size() , types[3]);	
	}
	while(spock--){
		population.insert(population.begin() + rand() % population.size() , types[4]);	
	}
}

void match(int games){
	int playerOne, playerTwo;
	while(games--){
		playerOne = rand()%population.size();
		playerTwo = rand()%population.size();
		if(population[playerOne] != population[playerTwo]){
			if(population[playerOne]->beatOne == population[playerTwo] ||
			 population[playerOne]->beatTwo == population[playerTwo]) { // player 1 wins
				population[playerTwo] = population[playerOne];
			} else { // player 2 wins
				population[playerOne] = population[playerTwo];
			}
		}
	}
}

void outputToFile(){
	int count[5];
	memset(count, 0, sizeof(count)); 
	for(int i = 0; i < population.size(); ++i){
		count[population[i]->type]++;
	}
	myfile /* << population.size() << */ << " "  << count[0] << " " << count[1] << " " << count[2] << " " << count[3] << " " << count[4] << endl;
}


int main() {
	srand (time(NULL));
	myfile.open("RPSLS.txt");
	initialize();
	generatePopulation(40000,40000,40000,40000,200);
	myfile << "generation " << "rock " << "paper " << "scissors " << "lizzard " << "spock" << endl;
	myfile << 0 << " ";
	//generatePopulation(100000);
	outputToFile();
	int generation = 40000;
	
	while(generation--){
		match(10000);
		myfile << 40000-generation;
		outputToFile();
	}
}