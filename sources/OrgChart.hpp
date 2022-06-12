#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <stack>

using namespace std;

namespace ariel{
    class OrgChart{
        struct Node{
            Node *root;
            vector<Node *> leaf;
            string data; 
            Node(const string &value, Node *node, vector<Node *> leaf):data(value), root(node), leaf(move(leaf)){}
            };
            Node *root;
            Node *NodeFinder(Node *n, const string &roott);
            enum Iterator_type{
                preorder,
                level,
                reverse
            };
        class Iterator{
            private:
                queue<Node *> queue1;
                queue<Node *> queue2; 
                stack<Node *> stackk;  
                queue<Node *> queue3;
                vector<Node *> leaf;
                Node* root;
                Iterator_type it;
            public:
                // Node* root;
                // Iterator_type it;
                Iterator(){
                    root=nullptr;
                    it=level;
                };
                Iterator(Node *node){
                    it=level;
                    root=node;
                }
                Iterator(Node *node, Iterator_type t):root(node) , it(t){
                    init(node);
                }
                Iterator &operator++();
                bool operator==(const Iterator &otherIterator) const;
                bool operator!=(const Iterator &otherIterator) const;
                string &operator*();
                string *operator->();
                //vector<Node *> get();
                void init(Node *p);
        };
        public:
            OrgChart():root(nullptr){};
            ~OrgChart(){
                delete_chart(root);
            }
            void delete_chart(Node *n);
            OrgChart &add_root(const string &roott); 
            OrgChart &add_sub(const string &parent, const string &child); 
            friend ostream &operator<<(ostream &out, const OrgChart &orgin);
            Iterator begin_level_order();
            Iterator begin_reverse_order();
            Iterator begin_preorder();
            Iterator end_level_order();
            Iterator reverse_order();
            Iterator end_preorder();
            Iterator begin();
            Iterator end();
    };
};