typedef struct PlayerNode{
	int pnum;
	struct PlayerNode* curr;
	struct PlayerNode* prev;
	struct PlayerNode* next;
}PNode;

typedef PNode* PNodeptr;
#define PBOX (PNodeptr)malloc(sizeof(PNode))

PNodeptr createPlayers(int playerCount){
	int flag=1; //check if head is to be created
	PNodeptr head, temp;
	for(int pnum=1; pnum<=playerCount; pnum++){
		PNodeptr node = PBOX;
		node->pnum = pnum;
		node->curr = node;
		node->next = NULL;
		node->prev = NULL;
		if(flag){
			head = node;
			flag = 0;
		}else{
			temp->next = node;
			node->prev = temp;
		}
		temp = node;
		if(pnum==playerCount){
			node->next = head;
			head->prev = node;
		}
	}
	return head;
}

char getPlayerName(int pnum){
	switch(pnum){
		case 1:
			return 'A';
			break;
		case 2:
			return 'B';
			break;
		case 3:
			return 'C';
			break;
		case 4:
			return 'D';
			break;
	}
}
