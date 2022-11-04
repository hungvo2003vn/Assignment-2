#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ConcatStringTree {

public:
    struct Node {
        int leftLength;
        int length;
        string data;
        Node* left;
        Node* right;
        Node(int LLen=0, int len=0, string s="", Node* L = NULL, Node* R = NULL) {
            leftLength = LLen;
            length = len;
            data = s;
            left = L;
            right = R;
        }
    };
    Node* Root;
public:
    ConcatStringTree();
    ConcatStringTree(const char * s);
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;

    //Helper Function
    Node* search_index(Node* cur, int& index);
    int search_dfs(Node* cur, int& index, char c);

    string pre_order(Node* cur) const;
    string toStringNode(Node* cur) const;

    string toString_helper(Node* cur) const;

    Node* combine(Node* L, Node* R) const;
    Node* build_bottom(Node* root, int start, int from, int to) const;

    Node* deepRe(Node* cur) const;
};
/*
class ReducedConcatStringTree; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
};

class ReducedConcatStringTree /* */ //{
/*
public:
    class LitStringHash {
    public:
        LitStringHash(const HashConfig & hashConfig);
        int getLastInsertedIndex() const;
        string toString() const;
    };

public:
    static LitStringHash litStringHash;
};*/

#endif // __CONCAT_STRING_TREE_H__