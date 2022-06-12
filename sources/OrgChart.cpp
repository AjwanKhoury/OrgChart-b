#include <iostream>
#include "OrgChart.hpp"
#include <stack>
#include <queue>
using namespace std;

using namespace ariel;
    
    //recieve a root as an input and add it to the tree root. 
    //if there's already root so replace it.
    OrgChart& OrgChart:: add_root(const string &roott){ 
        //at the first we check if the root is empty , if it so throw execption
        if(roott.empty()){throw std::invalid_argument("its empty at all!");}
        //else if the root is null
        if(root != nullptr){
            //so we create node the node input(string, Node, vector)
            Node *newone=new Node(roott, nullptr, root->leaf);
            //update the root to be the newone node that we created
            root=newone;
        }
        else{
            //else if already have e root so we c=have to replace it.
            root=new Node(roott, nullptr, vector<Node *>());
        }
        return *this;
    }
    //to find the node itself
    OrgChart::Node* OrgChart::NodeFinder(Node *n, const string &roott){
        //we must check if the input node that we got is null if it so throw exepction
        if(n==nullptr){throw std::invalid_argument("there's no node at all");}
        //we also must check if the data that we got is equall to this in the root , if it so return this node
        if(n->data==roott){return n;}
        //for(size_t i : n->leaf.size()){
        //else we must loop over the leafs to find the  node
        for(size_t i=0; i< n->leaf.size();i++){
            Node *t = NodeFinder(n->leaf.at(i), roott);
            if(t != nullptr){return t;}
        }
        return nullptr;
    }
    //we get two inputs,person that already exsits and another one who report the first
    OrgChart& OrgChart:: add_sub(const string &parent, const string &child){
        //check if exsits person at all' if not so throw exception
        if(parent.empty()){throw std::invalid_argument("there's no parent node at all");}
        //and check if another one who report the first is exsits if not so throw exception
        if(child.empty()){throw std::invalid_argument("there's no child node at all");}
        //else we use the help function nodefinder 
        Node* p=NodeFinder(root,parent);
        //if we don't find so throw exception
        if(p==nullptr){throw std::invalid_argument("there's no parent at all");}
        //else we create another node to this child
        Node *c= new Node(child,p,vector<Node *>());
        p->leaf.push_back(c);
        return *this;
    }
    //Returns iterators for the purpose of passing in 
    //the order(father - son - son - grandson).
    OrgChart::Iterator OrgChart::begin_level_order(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(root,level);
    }
    //Returns iterators for transition 
    //in order (father - son - grandson - son - grandson)
    OrgChart::Iterator OrgChart::begin_preorder(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(root,preorder);
    }
    //Returns iterators for a reverse level order.
    //(grandson - grandson - son - son - father).
    OrgChart::Iterator OrgChart::begin_reverse_order(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(root,reverse);
    }
    OrgChart::Iterator OrgChart::end_level_order(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::end_preorder(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::reverse_order(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::begin(){
        if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(root,level);
    }
    OrgChart::Iterator OrgChart::end(){
         if(this->root==nullptr){throw std::invalid_argument("there's no root");}
        return Iterator(nullptr);
    }
    string* OrgChart::Iterator::operator->(){
        //return &(this->root->data);
        return &queue1.front()->data;
    }
    string &OrgChart:: Iterator::operator*(){
        // return this->root->data;
        return queue1.front()->data;
    }
    bool OrgChart::Iterator::operator!=(const Iterator &otherIterator)const{
        if (queue1.empty()){return false;}
        return !(*this == otherIterator);
    }
    bool OrgChart::Iterator::operator==(const Iterator &otherIterator)const{
        return this->root == otherIterator.root;
    }
    OrgChart::Iterator &OrgChart::Iterator::operator++(){
        // if(this->leaf.size()>1){
        //     this->leaf.erase(this->leaf.begin());
        //     this->root=this->leaf.at(0);
        // }
        // else{ this->root=nullptr;}
        // return *this;
        if (queue1.empty()){ *this = Iterator(nullptr);}
        if (!queue1.empty()){queue1.pop();}
        return *this;
    }
    // vector<Node *> OrgChart::Iterator::get(){
    //     return this->leaf;
    // }
    ostream &ariel::operator<<(ostream& out, const OrgChart &orgin){
        // OrgChart::Iterator it=OrgChart::Iterator(org.root,OrgChart::level);
        // //vector<Node *> v=it.get();
        // for(unsigned int i=0 ;i< leaf.size(); i++){
        //     out<<leaf.at(i)->data<<"--";
        // }
        // return out;
        
        //set a new queue of node * and push the orgchart to it
        queue<OrgChart::Node *> newqueue;
        newqueue.push(orgin.root);
        //check if its not null so:
        while (!newqueue.empty()) {
            //so set another temp of node for the front one
            OrgChart::Node *temp = newqueue.front();
            //and pop ir back from this queue
            newqueue.pop();
            //after pop if it null so print tha parent because he have no leaf.
            if (temp->leaf.empty()){ out << temp->data << ":--im a parent--";}
            //else he have children so print them 
            else{
                out << temp->data << ": ---these are my childlren---";
                //loop over the children to print them
                for (OrgChart::Node *childrenn : temp->leaf){
                    out << childrenn->data << " ";
                }
                out << endl;
                // then must push the leaf to this queue
                for (OrgChart::Node *childrenn : temp->leaf){
                    newqueue.push(childrenn);
                }
            }
        }
        return out;
    }
    
    // OrgChart::Iterator::Iterator(Node* node, Iterator_type t){
    //     if(node != nullptr){
    //         if(method == level){
    //             ite
    //         }
    //     }
    // }

    void OrgChart::Iterator::init(OrgChart::Node *p){
        // queue<Node*> tempq;
        // if(n=nullptr){throw std::invalid_argument("Its null!");}
        // tempq.push(n);
        // this->leaf.push_back(n);
        // Node* tempq=n;
        // while(!tempq.empty()){
        //     for(unsigned int i=0; i<tempq->leaf.size();i++){
        //         this->
        //     }
        // }

        //if the iterator is at a reverse order so:
        if (it == reverse){
            //we must push the root 2 our queue
            queue3.push(p);
            //while its not empty
            while (!queue3.empty()){
                //set a temporary stack
                stack<Node *> temp;
                //we loop over the first element and push it!
                for (Node *s : queue3.front()->leaf){
                    temp.push(s);
                }
                //if the temp stack isn't null so must push the first element to queue 3, and pop it from the stack
                while (!temp.empty()){
                    queue3.push(temp.top());
                    temp.pop();
                }
                //and push the first element to the stack then pop it from queue 3
                stackk.push(queue3.front());
                queue3.pop();
            }
            // to pass the stack by the defualt queue
            //while the stack isnt null
            while (!stackk.empty()){
                //must push upfrom the queue1 it the first elemnt at the stack and pop thee stack itself
                queue1.push(stackk.top());
                stackk.pop();
            }
        }
        
        //if the iterator is at a level order so:
        if (it == level){
            //we must push the root 2 our queue
            queue2.push(p);
            //while its not empty
            while (!queue2.empty()){
                //we loop over the first element and push it!
                for (Node *s : queue2.front()->leaf){
                    queue2.push(s);
                }
                //and push the first element to the queue1 then pop it from queue 2
                queue1.push(queue2.front());
                queue2.pop();
            }
        }
        //if the iterator is at a preorder so:
        else if (it == preorder){
            //we must push the root 2 stack
            stackk.push(p);
            //while the stack isn;t empty so
            while (!stackk.empty()){
                //set a the first element iin the stack as a temporary node
                Node *temp = stackk.top();
                //push the first temporary element to the queue and pop the stack
                queue1.push(temp);
                stackk.pop();
                //set another temporary stack and loop over the children
                stack<Node *> temp_stack;
                for (Node *t : temp->leaf){
                    //push his children
                    temp_stack.push(t);
                }
                //while its not null over so must push the first element from the stack at the temporary one
                while (!temp_stack.empty()){
                    stackk.push(temp_stack.top());
                    //and pop this temporary one
                    temp_stack.pop();
                }
            }
        }
    }
    //to delete..
    void OrgChart::delete_chart(OrgChart::Node *n){
        //if the node we got is null so theres nothing to remove
        if (n == nullptr){
            return;
        }
        // else we must loop over the child
        for (Node *child : n->leaf){
            //and then delete the leaf(Child)
            delete_chart(child);
        }
        //the n is the node we got
        delete n;
    }

        

