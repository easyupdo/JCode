/**hash_chaining.h
 * The Chaining Hash Table Data Structure in C++
 * Time Cost : Search / Insert / Delete : Θ(1)
 * Thanks to Introduction to Algorithms (CLRS) Chapter 11
 * Thanks to Stanford MOOC of "Algorithms : Part I"
 * Author: Zheng Chen / Arclabs001
 * Email : chenzheng17@yahoo.com
 * Copyright 2015 Xi'an University of Posts & Telecommunications. All rights reserved.
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node     //The hash chaining node
{
    int key;
    string name;
    Node * next;
};

class hash_table
{
private:
    vector<Node *> _map;
    int _hash(int _key) {return (_key*73)%101;}  //The hash function

public:
    hash_table() {_map.reserve(105); for(int i=0;i<=100;i++) _map[i]=nullptr;}  //Constructor

    void hash_insert(int _key, string _name);
    void hash_insert(Node* New_Node);

    void hash_delete(int _key);
    void hash_delete(int _key, string _name);
    void hash_delete(Node* node);

    Node* hash_search(int _key);
    Node* hash_search(int _key, string _name);
};
/**
 * Insert a node into the hash table
 * @param _key  : The key value
 * @param _name : One of the satelitte data 
 */
void hash_table::hash_insert(int _key, string _name)
{
    Node * New_Node = new Node;
    New_Node->key = _key;
    New_Node->name = _name;
    hash_insert(New_Node);
}
/**
 * Insert a node into the hash Table
 * @param New_Node : The node to be inserted
 */
void hash_table::hash_insert(Node* New_Node)
{
    int hash_id = _hash(New_Node->key);
    New_Node->next = _map[_hash(New_Node->key)];
    _map[_hash(New_Node->key)] = New_Node;
}
/**
 * Delete all of the node which value equals to key
 * @param _key : The key value
 */
void hash_table::hash_delete(int _key)
{
    if(_map[_hash(_key)] == nullptr)
       return;

    int num = _hash(_key);
    Node* p = _map[num];
    while(_map[num])
    {
        p = _map[num];
        _map[num] = p->next;
        delete p;
    }
}
/**
 * Delete a node which valued _key and name = _name
 * @param _key  : The key value
 * @param _name : One of the satelitte data 
 */
void hash_table::hash_delete(int _key, string _name)
{
    if(_map[_hash(_key)] == nullptr)
        return;

    int num = _hash(_key);
    Node * p = _map[num];
    Node * q = _map[num];
    while(p!=nullptr)
    {
        if(p->name == _name)
            break;
        q = p;
        p = p->next;
    }

    if(q == _map[num] && p == q)
        _map[num] = p->next;
    else
        q->next = p->next;
}
/**
 * Delete a node from the hash table which equals to node
 * @param node : The node to be deleted
 */
void hash_table::hash_delete(Node* node)
{
    hash_delete(node->key, node->name);
}
/**
 * Search the node which valued key
 * @param  _key : The key value
 * @return      : a pionter to the first node
 */
Node* hash_table::hash_search(int _key)
{
    return _map[_hash(_key)];
}
/**
 * Find a node which valued key and its name equals to _name
 * @param  _key  : The key value
 * @param  _name : One of the satelitte data 
 * @return       : A pionter to the target node
 */
Node* hash_table::hash_search(int _key, string _name)
{
    if(_map[_hash(_key)] == nullptr)
    {
        return nullptr;
    }

    Node* p = _map[_hash(_key)];
    while(p)
    {
        if(p->name == _name)
            return p;
        p = p->next;
    }
    return nullptr;
}


