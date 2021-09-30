#include "hash_chaining.h"

int main()
{
    hash_table _hash_table;
    Node *_node = _hash_table.hash_search(3);   //此时表为空，测试search
    if(_node == nullptr)
        cout<<"Now _node is a nullptr!"<<endl;

    string name = "asdfg";

    for(int i=0; i<5; i++)  //插入节点
    {
        name[i]++;
        _hash_table.hash_insert(i,name);
    }

    _node = _hash_table.hash_search(3);     //测试search(int _key)接口
    cout<<_node->name<<endl;

    _hash_table.hash_delete(3,"btegg");     //测试delete(int _key, string _name)接口
    _node = _hash_table.hash_search(3);
    if(_node == nullptr)
        cout<<"Now _node is a nullptr!"<<endl;
    else
        cout<<_node->name<<endl;

    _hash_table.hash_insert(2,"b");     //测试insert(int _key, string _name)接口

    _node = _hash_table.hash_search(2,"btefg");     //测试search(int _key, string _name)接口
        cout<<_node->name<<endl;

    _node = _hash_table.hash_search(2,"b"); 
        cout<<_node->name<<endl;

    _hash_table.hash_delete(2,"btefg");
    _node = _hash_table.hash_search(2);
    if(_node == nullptr)
        cout<<"Now _node is a nullptr!"<<endl;
    else
        cout<<_node->name<<endl;
    return 0;
}