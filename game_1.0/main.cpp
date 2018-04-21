#include<iostream>
#include<stdlib.h>
#include<map>
using namespace std;

#include "player_node.cpp"
#include "game_node.cpp"

int main(){
	int gameSize, playerCount;
	int flag=1;
	map<int, int, GNodeptr> gMap;
	typedef map<int, int, GNodeptr> GMap;
	
	while(flag){
		cout<<"Enter the size of the game (10-25): "; cin>>gameSize;
		if(gameSize>=10 && gameSize<=25) flag=0;
		else cout<<"Opps! Invalid size, please try again"<<endl;
	}

	flag=1;
	while(flag){
		cout<<"Enter the number of players (2-4): "; cin>>playerCount;
		if(playerCount>=2 && playerCount<=4) flag=0;
		else cout<<"Opps! Invalid number, please try again"<<endl;
	}
	
	int board[gameSize][gameSize][1];
	board = createBoard(gameSize, board, gMap);
	
	
}
