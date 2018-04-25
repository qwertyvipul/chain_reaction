#include<iostream>
#include<stdlib.h>
#include<map>
using namespace std;

#include "player_node.cpp"
#include "game_node.cpp"

typedef map<int, GNodeptr> GMap;

#include "chain_reaction.cpp"

int main(){
	system("Color F0");
	int gameSize, playerCount;
	int flag=1;
	
	while(flag){
		cout<<"Enter the size of the game (2-10): "; cin>>gameSize;
		if(gameSize>=2 && gameSize<=10) flag=0;
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
	
	
	//chainReaction.printRawNodeCount(); //to check if all the node counts were correct
	//chainReaction.printRawGame(); //to print the layout of the board
	//for(int i=0; i<gameSize*gameSize; i++){cout<<chainReaction.gmap[i]<<endl;} //just a check if the map was successfully created
}

/*
-----------
| 00 | 00 |
| 00 | 00 |
-----------
| 00 | 00 |
| 00 | 00 |
-----------
xxxxxxxxxxx
*/
