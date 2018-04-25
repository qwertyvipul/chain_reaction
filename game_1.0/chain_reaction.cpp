class ChainReaction{
	public: //Yes I know, but can't resist the easy way ;-)
		int gameSize;
		int playerCount;
		GMap gmap;
		PNodeptr firstPlayer;
		
		ChainReaction(int, int);
		
		//forward declaration for nested calls
		void createGame();
		void printRawGame();
		void printGame();
		void printRawNodeCount();
		void play();
		void markIndex(PNodeptr, int);
		int gameLeft();
		int playerLeft(PNodeptr);
		void burstNode(GNodeptr);
		void burstLeft(GNodeptr, PNodeptr);
		void burstRight(GNodeptr, PNodeptr);
		void burstUp(GNodeptr, PNodeptr);
		void burstDown(GNodeptr, PNodeptr);
};

ChainReaction::ChainReaction(int gameSize, int playerCount){
	this->gameSize = gameSize;
	this->playerCount = playerCount;
}

void ChainReaction::createGame(){
	this->firstPlayer = createPlayers(this->playerCount);
	GNodeptr up, left;
	for(int rownum = 0; rownum<this->gameSize; rownum++){
		if(rownum == 0) up = NULL;
		for(int colnum = 0; colnum<this->gameSize; colnum++){
			if(colnum == 0) left = NULL;
			int index = rownum*gameSize + colnum;
			GNodeptr node = GBOX;
			gmap[index] = node;
			node->index = index;
			node->player = NULL;
			node->count = 0;
			node->total = 0;
			if(rownum==0){
				node->up = NULL;
			}else{
				int uindex = ((index/this->gameSize-1)*this->gameSize + index%this->gameSize);
				node->up = this->gmap[uindex];
				node->total++;
				node->up->down = node;
				node->up->total++;
			}
			
			if(colnum==0){
				node->left = NULL;
			}else{
				int lindex = index-1;
				node->left = this->gmap[lindex];
				node->total++;
				node->left->right = node;
				node->left->total++;
			}
		}
	}
}

void ChainReaction::play(){
	
	//get the first moves to initialize the game
	PNodeptr pnode = this->firstPlayer;
	do{
		this->printGame();
		cout<<"Player "<<getPlayerName(pnode->pnum)<<" please enter your index: ";
		int index;
		cin>>index;
		while(index>=this->gameSize*this->gameSize || this->gmap[index]->player!=0){
			cout<<"Please choose a valid index: "; cin>>index;
		}
		this->markIndex(pnode, index);
		pnode = pnode->next;
	}while(pnode!=this->firstPlayer);
	
	//the game has already begun!!!
	do{
		if(this->playerLeft(pnode)){
			this->printGame();
			cout<<"Player "<<getPlayerName(pnode->pnum)<<" please enter your index: ";
			int index;
			cin>>index;
			while(index>=this->gameSize*this->gameSize || this->gmap[index]->count == this->gmap[index]->total || (this->gmap[index]->player!=NULL && this->gmap[index]->player!=pnode)){
				cout<<"Please choose a valid index: "; cin>>index;
			}
			this->markIndex(pnode, index);
			pnode = pnode->next;
		}else{
			cout<<"Opps Player "<<getPlayerName(pnode->pnum)<<" you have been knocked out of the game."<<endl;
			pnode->next->prev = pnode->prev;
			pnode->prev->next = pnode->next;
			pnode = pnode->next;
			
			if(pnode->next == pnode){
				cout<<"Hurrah! Player "<<getPlayerName(pnode->pnum)<<" has won the game."<<endl;
				return;
			}
		}
	}while(this->gameLeft());
	//cout<<"Hurrah! "<<getPlayerName(pnode->prev->pnum)<<" has won the game."<<endl;
	//this->printGame();
}


int ChainReaction::gameLeft(){
	for(int index=0; index<this->gameSize*this->gameSize; index++){
		if(this->gmap[index]->count<this->gmap[index]->total) return 1;
	}
	return 0;
}

int ChainReaction::playerLeft(PNodeptr pnode){
	for(int index=0; index<this->gameSize*this->gameSize; index++){
		if(this->gmap[index]->player == pnode) return 1;
	}
	return 0;
}


void ChainReaction::markIndex(PNodeptr pnode, int index){
	GNodeptr gnode = this->gmap[index];
	gnode->player = pnode;
	gnode->count++;
	
	if(gnode->count == gnode->total) this->burstNode(gnode);
}

void ChainReaction::printGame(){
	for(int i=0; i<(this->gameSize)*5+1; i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			if(index/10==0) cout<<" 0";
			else cout<<" ";
			cout<<index<<" |";
		}
		cout<<endl;
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			GNodeptr node = this->gmap[index];
			if(node->player == NULL){
				cout<<" 00 |";
			}else{
				cout<<" "<<getPlayerName(node->player->pnum)<<node->count<<" |";
			}
		}
		cout<<endl;
		for(int i=0; i<(this->gameSize)*5+1; i++){
			cout<<"-";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize)*5+1; i++){
		cout<<"x";
	}
	cout<<endl;
}


void ChainReaction::printRawGame(){
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			if(index/10==0) cout<<"0";
			cout<<index<<"|";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
}

void ChainReaction::printRawNodeCount(){
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			cout<<"0"<<this->gmap[index]->total<<"|";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
}

void ChainReaction::burstNode(GNodeptr gnode){
	cout<<"Node Burst"<<endl;
	gnode->count=0;
	PNodeptr player = gnode->player;
	gnode->player = NULL;
	this->burstLeft(gnode, player);
	this->burstRight(gnode, player);
	this->burstUp(gnode, player);
	this->burstDown(gnode, player);
	cout<<"Burst Over"<<endl;
}

void ChainReaction::burstLeft(GNodeptr gnode, PNodeptr player){
	if(gnode->left == NULL) return;
	cout<<"Left Burst"<<endl;
	this->markIndex(player, gnode->left->index);
}

void ChainReaction::burstRight(GNodeptr gnode, PNodeptr player){
	if(gnode->right == NULL) return;
	cout<<"Right Burst"<<endl;
	this->markIndex(player, gnode->right->index);
}

void ChainReaction::burstUp(GNodeptr gnode, PNodeptr player){
	if(gnode->up == NULL) return;
	cout<<"UP Burst"<<endl;
	this->markIndex(player, gnode->up->index);
}

void ChainReaction::burstDown(GNodeptr gnode, PNodeptr player){
	if(gnode->down == NULL) return;
	cout<<"Down Burst"<<endl;
	this->markIndex(player, gnode->down->index);
}


