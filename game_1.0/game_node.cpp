typedef struct GameNode{
	int rownum;
	int colnum;
	int player;
	int count;
	struct GameNode* up;
	struct GameNode* down;
	struct GameNode* left;
	struct GameNode* right;
}GNode;

typedef GNode* GNodeptr;
#define GBOX (GNode*)malloc(sizeof(GNode))

int* createBoard(int gameSize, int* board, &gMap){
	GNodeptr unode, dnode, lnode, rnode;
	for(int i=0; i<gameSize; i++){
		if(i%gameSize == 0) unode = NULL;
		for(int j=0; j<gameSize; j++){
			if(j%gameSize == 0) lnode = NULL;
			board[i][j][1] = 0;
			GNodeptr node = GBOX;
			node->rownum = i;
			node->colnum = j;
			node->player = 0;
			node->count = 0;
			node->up = NULL;
			node->down = NULL;
			node->left = NULL;
			node->right = NULL;
			gMap[i][j]
		}
	}
}

/*
-------------------------------
----01 02 03 04 05 06 07 08 09
01-|00|00|00|00|00|00|00|00|00|
02-|00|00|00|00|00|00|00|00|00|
03-|00|00|00|00|00|00|00|00|00|
04-|00|00|00|00|00|00|00|00|00|
05-|00|00|00|00|00|00|00|00|00|
06-|00|00|00|00|00|00|00|00|00|
07-|00|00|00|00|00|00|00|00|00|
08-|00|00|00|00|00|00|00|00|00|
09-|00|00|00|00|00|00|00|00|00|
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
