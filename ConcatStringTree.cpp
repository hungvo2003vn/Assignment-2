#include "ConcatStringTree.h"

ConcatStringTree::ConcatStringTree() {
	Root = NULL;
}
ConcatStringTree::ConcatStringTree(const char* s) {

	string tmp = string(s);
	Root = new Node(0,(int)tmp.length(), tmp, NULL, NULL);
}
//Get length
int ConcatStringTree::length() const {
	return Root->length;
}
//Get char at index
ConcatStringTree::Node* ConcatStringTree::search_index(Node* cur, int &index) {
	if (!cur->left && !cur->right) return cur;
	if (index < cur->leftLength)
		return search_index(cur->left, index);
	else 
	{
		index -= cur->leftLength;
		return search_index(cur->right, index);
	}
}
char ConcatStringTree::get(int index) {
	if (!(0 <= index && index < Root->length ))
		throw out_of_range("Index of string is invalid!");
	Node* cur = search_index(Root, index);
	return cur->data[index];
}
//Get index of char
int ConcatStringTree::search_dfs(Node* cur, int& index, char c) {
	if (!cur) return -1;

	if (!cur->left && !cur->right)
	{
		int pos = (int)cur->data.find(c);
		if (pos != string::npos) 
		{
			index += pos;
			return index;
		}
		else 
		{
			index += (int)cur->data.length();
			return -1;
		}
	}
	int pos_left = search_dfs(cur->left, index, c);
	if (pos_left != -1) return pos_left;

	int pos_right = search_dfs(cur->right, index, c);
	if (pos_right != -1) return pos_right;

	return -1;
}
int ConcatStringTree::indexOf(char c) {
	int index = 0;
	return search_dfs(Root, index, c);
}
//PreOrder
string ConcatStringTree::toStringNode(Node* cur) const{

	if (!cur) return "";

	string ans = "(LL=" + to_string(cur->leftLength) + "," +
		"L=" + to_string(cur->length) + ",";

	if (cur->left || cur->right) ans += "<NULL>)";
	else ans += "\"" + cur->data + "\")";

	return ans;
}
string ConcatStringTree::pre_order(Node* cur) const {

	if (!cur) return "";
	
	string ans = toStringNode(cur);
	if (cur->left) ans += ";" + pre_order(cur->left);
	if (cur->right) ans += ";" + pre_order(cur->right);
	return ans;
}
string ConcatStringTree::toStringPreOrder() const{

	string ans = "\"ConcatStringTree[" + pre_order(Root) + "]\"";
	return ans;
}
//Tostring 
string ConcatStringTree::toString_helper(Node* cur) const {
	if (!cur) return "";
	else return cur->data + toString_helper(cur->left) + toString_helper(cur->right);
}
string ConcatStringTree::toString() const {
	string ans = "\"ConcatStringTree[\"" 
		+ toString_helper(Root) + "\"]\"";
	return ans;
}
//Concat
ConcatStringTree ConcatStringTree::concat(const ConcatStringTree& otherS) const {

	ConcatStringTree* ans = new ConcatStringTree();
	ans->Root = new Node(Root->length, Root->length + otherS.Root->length, "", Root, otherS.Root );
	return *ans;
}
//subStr
ConcatStringTree::Node* ConcatStringTree::combine(Node* L,Node* R) const {
	
	if (!L && !R) return NULL;

	Node* root = new Node(0,0,"",L,R);

	if (L) root->leftLength = L->length;
	root->length = root->leftLength;
	if (R) root->length += R->length;

	return root;
}
ConcatStringTree::Node* ConcatStringTree::build_bottom(Node* cur, int start, int from, int to) const {
	
	if (!cur) return NULL;
	if (!cur->left && !cur->right) 
	{
		if (start >= to || start + cur->length - 1 <from) return NULL;
		if (start <= from && from < start + cur->length) 
		{
			Node* tmp = new Node(0, 0, cur->data.substr(from - start, min(cur->length+start - from,to-from)), NULL, NULL);
			return tmp;
		}
		else if (start < to && to <= start + cur->length)
		{
			Node* tmp = new Node(0, 0, cur->data.substr(0, to - start), NULL, NULL);
			return tmp;
		}
		else {
			Node* tmp = new Node(0, 0, cur->data, NULL, NULL);
			return tmp;
		}
	}
	else return combine(build_bottom(cur->left,start,from,to), build_bottom(cur->right,start+cur->leftLength,from,to));
}
ConcatStringTree ConcatStringTree::subString(int from, int to) const {
	if (from<0 || to>Root->length) 
		throw out_of_range("Index of string is invalid!");
	if (from >= to) 
		throw logic_error("Invalid range!");

	ConcatStringTree* ans = new ConcatStringTree();
	ans->Root = build_bottom(Root, 0, from, to);
	return *ans;
}
//Reverse
ConcatStringTree::Node* ConcatStringTree::deepRe(Node* cur) const{
	if (!cur) return NULL;
	
	string s = string(cur->data.rbegin(), cur->data.rend());
	Node* new_ele = new Node(cur->length-cur->leftLength,cur->length,s,NULL,NULL);

	new_ele->left = deepRe(cur->right);
	new_ele->right = deepRe(cur->left);
	return new_ele;
}
ConcatStringTree ConcatStringTree::reverse() const {
	ConcatStringTree* ans = new ConcatStringTree();
	ans->Root = deepRe(Root);
	return *ans;
}
//////////////////////PARENTSTREE IMPLEMENTATION/////////////////////////
ParentsTree::ParentsTree() {
	Root = NULL;
	max_ID = 0;
	nums_node = 0;
}
int ParentsTree::size() const {
	return this->nums_node;
}
int ParentsTree::height(ParNode* cur) {
	if (!cur) return 0;
	return cur->height;
}
int ParentsTree::getBalance(ParNode* cur) {
	if (!cur) return 0;
	return height(cur->left) - height(cur->right);
}
ParentsTree::ParNode* ParentsTree::Rtate(ParNode* cur) {
	ParNode* L = cur->left;
	ParNode* tmp = L->right;

	//Rotate
	L->right = cur;
	cur->left = tmp;
	//Update heights
	cur->height = max(height(cur->left), height(cur->right)) + 1;
	L->height= max(height(L->left), height(L->right)) + 1;

	return L;
}
ParentsTree::ParNode* ParentsTree::Ltate(ParNode* cur) {
	ParNode* R = cur->right;
	ParNode* tmp = R->left;

	//Rotate
	R->left = cur;
	cur->right = tmp;
	//Update heights
	cur->height = max(height(cur->left), height(cur->right)) + 1;
	R->height = max(height(R->left), height(R->right)) + 1;

	return R;
}
ParentsTree::ParNode* ParentsTree::MaxNode(ParNode* cur) {
	ParNode* start = cur;
	while (start && start->right) start = start->right;
	return start;
}
ParentsTree::ParNode* ParentsTree::insert(ParNode* cur, ParNode* ele) {
	if (!cur) return ele;

	if (ele->id < cur->id) cur->left = insert(cur->left, ele);
	else if (ele->id > cur->id) cur->right = insert(cur->right, ele);
	else return cur;

	//Update height
	cur->height = max(height(cur->left), height(cur->right)) + 1;
	int balance = getBalance(cur);

	//LL rotate case
	if (balance > 1 && cur->id < cur->left->id) return Rtate(cur);
	//RR rotate case
	if (balance < -1 && cur->id > cur->right->id) return Ltate(cur);
	//LR rotate case
	if (balance > 1 && cur->id > cur->left->id) 
	{
		cur->left = Ltate(cur->left);
		return Rtate(cur);
	}
	//RL rotate case
	if (balance < -1 && cur->id < cur->right->id)
	{
		cur->right = Rtate(cur->right);
		return Ltate(cur);
	}

	return cur;
}
ParentsTree::ParNode* ParentsTree::remove(ParNode* cur, int key) {
	if (!cur) return cur;

	if (key < cur->id) cur->left = remove(cur->left, key);
	else if (key > cur->id) cur->right = remove(cur->right, key);
	else 
	{
		if (!cur->left || !cur->right) 
		{
			ParNode* tmp = cur->left ? cur->left : cur->right;
			if (!tmp)
			{
				tmp = cur;
				cur = NULL;
			}
			else *cur = *tmp;

			delete(tmp); ////////////// WARNING!!!!!!!!!
			tmp = NULL;
		}
		else 
		{
			ParNode* tmp = MaxNode(cur->left);
			cur->id = tmp->id;
			cur->left = remove(cur->left, tmp->id);
		}
	}
	if (!cur) return cur;
	//Update height
	cur->height= max(height(cur->left), height(cur->right)) + 1;

	//Balance step
	int balance = getBalance(cur);

	//LL rotate case
	if (balance > 1 && getBalance(cur->left) >= 0)
		return Rtate(cur);
	//LR rotate case
	if (balance > 1 && getBalance(cur->left) < 0) 
	{
		cur->left = Ltate(cur->left);
		return Rtate(cur);
	}
	//RR rotate case
	if (balance < -1 && getBalance(cur->right) <= 0)
		return Ltate(cur);
	//RL rotate case
	if (balance < -1 && getBalance(cur->right) > 0)
	{
		cur->right = Rtate(cur->right);
		return Ltate(cur);
	}

	return cur;
}
string ParentsTree::Format_ParNode(ParNode* cur) const{
	if (!cur) return "";
	string ans = "(id=" + to_string(cur->id) + ")";
	return ans;
}
string ParentsTree::PreOrder(ParNode* cur) const{
	if (!cur) return "";

	string ans = Format_ParNode(cur);
	if (cur->left) ans += ";" + PreOrder(cur->left);
	if (cur->right) ans += ";" + PreOrder(cur->right);

	return ans;
}
string ParentsTree::toStringPreOrder() const {
	string ans = "\"ParentsTree[" + PreOrder(Root) + "]\"";
	return ans;
}