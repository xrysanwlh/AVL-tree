/* 
* Noli Chrysa, 2780, nochrysoula@uth.gr
*/


#include "AVL.hpp"


/**** NODE CONSTRUCTOR ****/
AVL::Node::Node(const std::string& e, AVL::Node *parent, AVL::Node *left, AVL::Node *right){

	height = 1;  // initially is leaf

	this->element = e;
	this->parent = parent;
	this->left = left;
	this->right = right;

}


/**** GET PARENT ****/
AVL::Node * AVL::Node::getParent() const {
	return this->parent;
}

/**** GET LEFT ****/
AVL::Node * AVL::Node::getLeft() const {
	return this->left;
}


/**** GET RIGHT ****/
AVL::Node * AVL::Node::getRight() const {
	return this->right;
}

/**** GET ELEMENT ****/
std::string AVL::Node::getElement() const {
	return this->element;
}

/**** GET HEIGHT ****/
int AVL::Node::getHeight() const {
	return this->height;
}

/**** SET LEFT ****/
void AVL::Node::setLeft(AVL::Node *left) {
	this->left = left;
}

/**** SET RIGHT ****/
void AVL::Node::setRight(AVL::Node *right) {
	this->right = right;
}

/**** SET PARENT ****/
void AVL::Node::setParent(AVL::Node *parent) {
	this->parent = parent;
}

/**** SET ELEMENT ****/
void AVL::Node::setElement(std::string str) {
	this->element = str;
}

/**** IS LEFT ****/
bool AVL::Node::isLeft() const {

	if(this->parent != nullptr && this->parent->getLeft() == this)  
		return true;

	return false;

}


/**** IS RIGHT ****/
bool AVL::Node::isRight() const {

	if(this->parent != nullptr && this->parent->getRight() == this)
		return true;

	return false;

}

/**** RIGHT CHILD HEIGHT ****/
int AVL::Node::rightChildHeight() const {

	if(this->right == nullptr)
		return 0;
	else
		return this->right->height;
	
}


/**** LEFT CHILD HEIGHT ****/
int AVL::Node::leftChildHeight() const {

	if(this->left == nullptr)
		return 0;
	else
		return this->left->height;
	
}

 /**** UPDATE HEIGHT ****/
int AVL::Node::updateHeight() {

	if(leftChildHeight() > rightChildHeight())
		this->height = leftChildHeight() + 1;
	else
		this->height = rightChildHeight() + 1;

	return this->height;

}

/**** IS BALANCED ****/
bool AVL::Node::isBalanced() {
	int heightDif = leftChildHeight() - rightChildHeight();

	if(heightDif > MAX_HEIGHT_DIFF || heightDif < -MAX_HEIGHT_DIFF)
		return false;

	return true;
}


/**** ITERATOR CONSTRUCTOR ****/

AVL::Iterator::Iterator() {
    curNode = nullptr;
}


AVL::Iterator::Iterator(AVL::Node *rootNode){

	curNode = nullptr;
	//create an empty stack and push root to it
	if(rootNode != nullptr){
		stackOfNodes.push(rootNode);
		iterativePreorder();
	}

}

/**** ITERATIVE PREORDER ****/
void AVL::Iterator::iterativePreorder(){  

	if(stackOfNodes.empty() == false){
		// Pop the top item from stack
		curNode = stackOfNodes.top();
		stackOfNodes.pop();

		// Push right and left children of the popped node to stack
		if (curNode->getRight())
           stackOfNodes.push(curNode->getRight());
        if (curNode->getLeft())
            stackOfNodes.push(curNode->getLeft());
	}
	else {
		curNode = nullptr;
	}


}


/**** OPERATOR ++ ****/
AVL::Iterator& AVL::Iterator::operator++() {
    iterativePreorder();  //pop up the next node
    return *this;
}


/**** OPERATOR ++ with prev****/
AVL::Iterator AVL::Iterator::operator++(int a) {
    AVL::Iterator previousIterator(*this);  //keep previous iterator
    iterativePreorder();  //go to next one
    return previousIterator;
}

/**** OPERATOR* ****/
string AVL::Iterator::operator*() {
    return curNode->getElement();
}

/**** OPERATOR == ****/
bool AVL::Iterator::operator==(Iterator it){

	if(curNode == it.curNode){
		return true;
	}

	return false;
}

/**** OPERATOR != ****/
bool AVL::Iterator::operator!=(Iterator it){

	return !(*this == it);  //use operator== from above function

}

/**** BEGIN ****/
AVL::Iterator AVL::begin() const {
    AVL::Iterator firstElement(root);
    return firstElement;
}

/**** END ****/
AVL::Iterator AVL::end() const {
    AVL::Iterator lastELement;
    return lastELement;
}

/******************** AVL FUCTIONS ****************/

/**** AVL CONSTRUCTORS ****/
AVL::AVL() {
    size = 0;
    root = nullptr;
};

AVL::AVL(const AVL &AVLtoCopy){  //copy constructor
    AVL::Iterator begin, end, cur;
    begin = AVLtoCopy.begin();
    end = AVLtoCopy.end();

    for(cur = begin; cur != end; cur++){
        add(*cur);
    }
}


/**** ADD ****/
bool AVL::add(string str) {

    AVL::Node* insNode = insertNode(str); 

    if (insNode == nullptr) {
        return false;
    }
    else {
	    rebalance(insNode);
	    size++;
	    return true;
	}
}


/**** INSERT NODE ****/
AVL::Node* AVL::insertNode(string data){
	AVL::Node *newNode;

	if(size == 0){  //if tree empty, insert in root
		newNode = new AVL::Node (data, nullptr, nullptr, nullptr); 
		root = newNode;
		size = 1;
		return root;
	}

	AVL::Node *insNode = findNode(data, root);  //find return "parent" of the node we want to add
	if(insNode == nullptr)
		return nullptr;
	
	string insData = insNode->getElement();     //parent's data

	if(data == insData) 
		return nullptr;
	else {
		if(data < insData){  //new node left child of parent
			newNode = new AVL::Node (data, insNode, nullptr, nullptr); 
			insNode->setLeft(newNode);
			insNode->getLeft()->setElement(data);
			return insNode->getLeft();
		}
		else{                //new node right child of parent
			newNode = new AVL::Node (data, insNode, nullptr, nullptr);
			insNode->setRight(newNode);
			insNode->getRight()->setElement(data);
			return insNode->getRight();
		}
	}

}


/**** FIND NODE ****/
AVL::Node *AVL::findNode(string data, AVL::Node *cur){

	string curData = cur->getElement(); //node's data every recursive time

	//try to find the parent of the node we want to insert.
	if(data < curData){
		if(cur->getLeft() == nullptr)
			return cur;
		else
			return findNode(data, cur->getLeft());
	}
	else if( curData == data)
		return cur;
	else {
		if(cur->getRight() == nullptr)
			return cur;
		else
			return findNode(data, cur->getRight());
	}

	return nullptr;

}


/**** RMV ****/
bool AVL::rmv(string data){ 

	AVL::Node *parentNode = removeNode(data);
	if(parentNode == nullptr){
		return true;
	}
	rebalance(parentNode);  //rebalance tree after removing one node
	
	return false;

}


/**** REMOVE NODE ****/
AVL::Node* AVL::removeNode(string data){

	if((*this).size == 0)  //empty tree, no nodes to remove
		return nullptr;

	AVL::Node *delNode = findNode(data, root);  //find the parent of the node we want to delete
	string delData = delNode->getElement();		//parent's data

	if(data != delData)
		return nullptr;
	else {

		AVL::Node *returnNode;

		if(delNode->getLeft() == nullptr || delNode->getRight() == nullptr){
			returnNode = (delNode->getLeft() != nullptr ? delNode->getLeft() :
						  delNode->getRight() != nullptr ? delNode->getRight() :
					 	  delNode->getParent());
			deleteNode(delNode);
			return returnNode;
		}
		else {

			AVL::Node *cursor = delNode->getRight();
			AVL::Node *temp;
			AVL::Node *parentDelNode;

			while((temp = cursor->getLeft()) != nullptr)
				cursor = temp;

			AVL::Node *helpTemp;
			helpTemp = cursor;
			cursor = delNode;
			delNode = helpTemp;

			parentDelNode = cursor->getParent();
			deleteNode(cursor);
			return parentDelNode;
		}
	}
}


/**** DELETE NODE ****/
void AVL::deleteNode(AVL::Node *v){

	if((v->getLeft() != nullptr) && (v->getRight() != nullptr))
		return; //failed to delete it

	if(v == root){
		AVL::Node *notNullSonofv = (v->getLeft() != nullptr ? v->getLeft() : v->getRight());
		root = notNullSonofv;
		if(root != nullptr)
			root->setParent(nullptr);
	}
	else {
		AVL::Node *parentOfV = v->getParent();
		AVL::Node *notNullSonofv = (v->getLeft() != nullptr ? v->getLeft() : v->getRight());
		if(v->isLeft())
			parentOfV->setLeft(notNullSonofv);
		else
			parentOfV->setRight(notNullSonofv);
		if(notNullSonofv != nullptr)
			notNullSonofv->setParent(parentOfV);
	}
	size--;
	v->setLeft(nullptr);
	v->setRight(nullptr);
	v->setParent(nullptr);
}


/**** REBALANCE ****/
void AVL::rebalance(AVL::Node *v){

	if(v == nullptr)
		return;

	AVL::Node *u;
	AVL::Node *w;

	while(v != nullptr){
		v->updateHeight(); 
		if(!(v->isBalanced())){
			w = rebalanceSon(v);
			u = rebalanceSon(w);
			v = reconstruct(v,w,u);  //reconstruction of tree
			v->getLeft()->updateHeight();
			v->getRight()->updateHeight();
			v->updateHeight();
		}
		v = v->getParent();
	}

}


/**** REBALANCE SON ****/
AVL::Node *AVL::rebalanceSon(AVL::Node *v){

	if(v == nullptr)
		return nullptr;

	if(v->leftChildHeight() > v->rightChildHeight())
		return v->getLeft();
	else if(v->leftChildHeight() < v->rightChildHeight())
		return v->getRight();
	else if(v->isLeft())
		return v->getLeft();
	else return v->getRight();
}


/**** RECONSTRUCT ****/
AVL::Node *AVL::reconstruct(AVL::Node *v, AVL::Node *w, AVL::Node *u){

	if(w->isLeft() && u->isLeft()){  /* ---single right- rotation-- */
		if(!(v == root)){
			if(v->isLeft())
				v->getParent()->setLeft(w);
			else
				v->getParent()->setRight(w);

			w->setParent(v->getParent());

		}
		v->setLeft(w->getRight());
		if(w->getRight() != nullptr)
			w->getRight()->setParent(v);
		w->setRight(v);
		v->setParent(w);
		if(v == root){
			root = w;
			w->setParent(nullptr);
		}
		return w;
	}
	else if(w->isRight() && u->isRight()){   /* ---single left rotation---*/
		if(v != root){
			if(v->isRight())
				v->getParent()->setRight(w);
			else
				v->getParent()->setLeft(w);
			w->setParent(v->getParent());
		}
		v->setRight(w->getLeft());
		if(w->getLeft() != nullptr)
			w->getLeft()->setParent(v);
		w->setLeft(v);
		v->setParent(w);
		if(v==root){
			root = w;
			w->setParent(nullptr);
		}
		return w;
	}
	else if(u->isLeft()){           /* ---double left rotation---*/
		v->setRight(u->getLeft());
		if(u->getLeft() != nullptr)
			u->getLeft()->setParent(v);
		w->setLeft(u->getRight());
		if(u->getRight() != nullptr)
			u->getRight()->setParent(w);
		if(v != root){
			if(v->isRight())
				v->getParent()->setRight(u);
			else 
				v->getParent()->setLeft(u);
			u->setParent(v->getParent());
		}
		v->setParent(u);
		w->setParent(u);
		u->setLeft(v);
		u->setRight(w);
		if(v == root){
			root = u;
			u->setParent(nullptr);
		}
		return u;
	}
	else {                               /* ---double right rotation---*/  
		v->setLeft(u->getRight());
		if(u->getRight() != nullptr)
			u->getRight()->setParent(v);
		w->setRight(u->getLeft());
		if(u->getLeft() != nullptr)
			u->getLeft()->setParent(w);
		if(v != root){
			if(v->isLeft())
				v->getParent()->setLeft(u);
			else
				v->getParent()->setRight(u);
			u->setParent(v->getParent());
		}
		v->setParent(u);
		w->setParent(u);
		u->setLeft(w);
		u->setRight(v);
		if(v == root){
			root = u;
			u->setParent(nullptr);
		}
		return u;
	}

}


/**** CONTAINS ****/
bool AVL::contains(string data){

	AVL::Node *found = findNode(data, root); //find it

	if(found->getElement() == data)
		return true;

	return false;
}


/**** PRE_ORDER ****/
void AVL::pre_order(std::ostream& out) {
    AVL::Iterator begin, end, cur;

    begin = this->begin();
    end = this->end();

    for(cur = begin; cur!=end; cur++){
    	out << *cur << " ";
    }

}


/**** OPERATOR<< ****/
std::ostream& operator<<(std::ostream& out, const AVL& tree) {

    AVL::Iterator begin, end, cur;
    begin = tree.begin();
    end = tree.end();

    while(begin != end) {
        out << *begin << " ";
        begin++;
    }

    return out;
}


/**** OPERATOR= ****/
AVL& AVL::operator=(const AVL& avl) {
    AVL::Iterator begin, end, cur;
    begin = this->begin();
    end = this->end();

    freeAVLtree();

    begin = avl.begin();
    end = avl.end();

    for(cur = begin; cur!=end; cur++){
    	this->add(*cur);
    }

    return *this;
}


/**** OPERATOR+ ****/
AVL AVL::operator+(const AVL& avl) {
    AVL newAVL;
    AVL::Iterator begin, end, cur;
    begin = this->begin();
    end = this->end();

    for(cur = begin; cur!=end; cur++){
    	newAVL.add(*cur);
    }

    begin = avl.begin();
    end = avl.end();

    for(cur = begin; cur!=end; cur++){
    	newAVL.add(*cur);
    }

    return newAVL;
}


/**** OPERATOR+= ****/
AVL& AVL::operator+=(const AVL& avl) {
    AVL::Iterator begin, end, cur;
    begin = avl.begin();
    end = avl.end();

    for(cur = begin; cur!=end; cur++){
    	this->add(*cur);
    }

    return *this;
}


/**** OPERATOR+= ****/
AVL& AVL::operator+=(const string& e) {

    this->add(e);
    return *this;

}


/**** OPERATOR-= ****/
AVL& AVL::operator-=(const string& e) {
    
    this->rmv(e);
    return *this;
}


/**** OPERATOR+ ****/
AVL AVL::operator+(const string& e) {
    AVL newAVL(*this);
    newAVL.add(e);
    return newAVL;
}


/**** OPERATOR- ****/
AVL AVL::operator-(const string& e) {
    AVL newAVL(*this);
    newAVL.rmv(e);
    return newAVL;
}


/**** GET CUR NODE****/
AVL::Node* AVL::Iterator::getCurNode() const {
    return curNode;
}


/**** FREE AVL TREE****/
void AVL::freeAVLtree() {
    AVL::Iterator begin, end, cur;
    begin = this->begin();
    end = this->end();

    for(cur = begin; cur != end; cur++)
    	delete cur.getCurNode();

    size = 0;
    root = nullptr;
}


void AVL::print2DotFile(char *filename) {
    ofstream graphFile(filename, ios::out | ios:: trunc);

    if (!graphFile.is_open()) {
        cerr << "error in opening file for writing." << endl;
        graphFile.close();
        exit(-1);
    }
    graphFile << "digraph AVL {";

    AVL::Iterator begin, end;
    begin = this->begin();
    end = this->end();
    while ( begin != end) {
        AVL::Node *tmp =  begin.getCurNode();
        if (tmp->getLeft() != nullptr) {
            graphFile << tmp->getElement() << " -> ";
            graphFile << tmp->getLeft()->getElement() << ";\n";
        }
        if (tmp->getRight() != nullptr) {
            graphFile << tmp->getElement() << " -> ";
            graphFile << tmp->getRight()->getElement() << ";\n";
        }

        if (root == tmp && tmp->getLeft() == nullptr && tmp->getRight() == nullptr) {
            graphFile << tmp->getElement() << ";\n";
        }
        begin++;
    }
    graphFile << "}";
}