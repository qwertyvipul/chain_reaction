typedef struct PlayerNode{
	int player;
	struct PlayerNode* next;
}PNode;

typedef PNode* PNodeptr;
#define PBOX (PNodeptr)malloc(sizeof(PNode))

PNodeptr createPlayers(int playerCount){
	int flag=1; //check if head is to be created
	PNodeptr head, temp;
	for(int player=1; player<=playerCount; player++){
		PNodeptr node = PBOX;
		node->player = player;
		node->next = NULL;
		if(flag){
			head = node;
			flag = 0;
		}else{
			temp->next = node;
		}
		temp = node;
	}
	return head;
}
