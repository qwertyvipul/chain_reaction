#include<iostream>
#include<stdlib.h>
#include<map>
using namespace std;

#include "player_node.cpp"
#include "game_node.cpp"

typedef map<int, GNodeptr> GMap;

#include "chain_reaction.cpp"

int main(){
	int gameSize, playerCount;
	int flag=1;
	
	while(flag){
		cout<<"Enter the size of the game (5-10): "; cin>>gameSize;
		if(gameSize>=5 && gameSize<=10) flag=0;
		else cout<<"Opps! Invalid size, please try again"<<endl;
	}

	flag=1;
	while(flag){
		cout<<"Enter the number of players (2-4): "; cin>>playerCount;
		if(playerCount>=2 && playerCount<=4) flag=0;
		else cout<<"Opps! Invalid number, please try again"<<endl;
	}
	
	ChainReaction chainReaction(gameSize, playerCount);
	chainReaction.createGame();
	//chainReaction.printGame();
	chainReaction.play();
	
	
	//chainReaction.printRawGame(); //to print the layout of the board
	//just a check if the map was successfully created
	//for(int i=0; i<gameSize*gameSize; i++){cout<<chainReaction.gmap[i]<<endl;}
	
	/*
	----------------
	|00|01|02|03|04|
	|05|06|07|08|09|
	|10|11|12|13|14|
	|15|16|17|18|19|
	|20|21|22|23|24|
	----------------
	*/
}
