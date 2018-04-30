#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<map>
using namespace std;
#include "player_node.cpp" //importing the player nodes
#include "game_node.cpp" //importing the game nodes
typedef map<int, GNodeptr> GMap; //to map the game index to the game nodes
#include "chain_reaction.cpp" //importing our game

int main(){
	int gameSize, playerCount;
	int flag=1; //for things that flag does
	int self=0;
	
	char ch;
	cout<<"Do you want to play with the system(y/n): "; cin>>ch;
	if(ch=='y'){
		cout<<"System is player A!"<<endl;
		self = 1;
	}
	
	while(flag){ //see the flag :-)
		cout<<"Enter the size of the game (2-10): "; cin>>gameSize; //limiting the game size
		if(gameSize>=2 && gameSize<=10) flag=0;
		else cout<<"Opps! Invalid size, please try again"<<endl;
	}

	flag=1;
	while(flag){
		cout<<"Enter the number of players (2-4): "; cin>>playerCount; //limiting the number of players
		if(playerCount>=2 && playerCount<=4) flag=0;
		else cout<<"Opps! Invalid number, please try again"<<endl;
	}
	
	ChainReaction chainReaction(self, gameSize, playerCount); //creating a instance of the game
	chainReaction.play(); //and the game begins
	cout<<"Press any key to finish: "; getch();
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
