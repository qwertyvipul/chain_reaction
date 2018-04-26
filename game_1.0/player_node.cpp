typedef struct PlayerNode{ //circular linked list
	int pnum; //the number associated with player
	struct PlayerNode* prev; //the previous player
	struct PlayerNode* next; //the next player
}PNode; //the player node

typedef PNode* PNodeptr; //the player node pointer
#define PBOX (PNodeptr)malloc(sizeof(PNode)) //memory allocation to the player node

//this creates the players
PNodeptr createPlayers(int playerCount){
	int flag=1; //check if head is to be created
	PNodeptr head, temp;
	for(int pnum=1; pnum<=playerCount; pnum++){
		PNodeptr node = PBOX;
		node->pnum = pnum;
		node->next = NULL;
		node->prev = NULL;
		if(flag){ //if head not created
			head = node;
			flag = 0;
		}else{
			temp->next = node; //previous node points to this node
			node->prev = temp; //this node points to the previous node
		}
		temp = node;
		if(pnum==playerCount){ //if last node
			node->next = head; //last node points to head
			head->prev = node; //head points to the last node
		}
	}
	return head; //returns the first player
}


//return the name of the players
char getPlayerName(int pnum){ 
	switch(pnum){
		case 1:
			system("Color F0");
			return 'A';
			break;
		case 2:
			system("Color E0");
			return 'B';
			break;
		case 3:
			system("Color A0");
			return 'C';
			break;
		case 4:
			system("Color B0");
			return 'D';
			break;
	}
}

/*
Color attributes are specified by TWO hex digits -- the first
corresponds to the background; the second the foreground.  Each digit
can be any of the following values:

    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
*/
