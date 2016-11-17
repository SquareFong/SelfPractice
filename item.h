#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <list>
#include <iostream>
#include <iomanip>
using namespace std;

class node{
    friend class tree;
    //item including root, document, file & storage
    //it's an simulation of things you can see in a file manager
    struct item{
        string _name;
        char _type;//r->root d->document f->file s->storage
        const time_t _created_time;
        time_t _changed_time;
        size_t _size;
        /*string getTime(){
            time_t now;
            now=time(NULL);
            struct tm * t=localtime(&now);
            return asctime(t);
        }*/
    public:
        item(const string name,const char type,const size_t s=0):_name(name),_type(type),
            _created_time(time(NULL)),_changed_time(_created_time),_size(s){

        }
        string get_created_time(){
            struct tm * t=localtime(&_created_time);
            string temp(asctime(t));
            temp[temp.size()-1]='\0';

            return temp;
        }

        string get_changed_time(){
            struct tm * t=localtime(&_changed_time);
            string temp(asctime(t));
            temp[temp.size()-1]='\0';
            return temp;
        }

        void setChangedTime(time_t temp_time){
            _changed_time=temp_time;
        }

        void setSize(const size_t size){
            _size=size;
            setChangedTime(time(NULL));
        }

        void rename(const string name){
            _name=name;
        }
    };

    item *_item;
    node *_back;
    list<node*> contents;
    typedef list<node*>::iterator p_node;
    void updateChangeTime(){
        time_t temp=time(NULL);
        node *t=this;
        while(t->_item->_type != 'r'){
            t->_item->setChangedTime(temp);
            t=t->_back;
        }
    }
    //unsigned fileNum,docNum;


public:
    node(node *back,const string name,const char type):_item(new item(name,type)),_back(back){
        if((back==nullptr)&&(type!='r'))
            exit(1);
    }
    //delete itself and its left tree
    ~node(){
        delete _item;
        while(!contents.empty()){
            delete (*contents.begin());
            contents.pop_front();
        }
    }
    //make directory
    bool mkDir(const string &name){
        for(unsigned i(0);i<name.size();++i){
            if(name[i]==' '||name[i]=='\\'||name[i]=='/' ){
                cout<<"cannot use this name, please try another"<<endl;
                return 0;
            }
        }
        for(p_node i=contents.begin();i!=contents.end()&&(*i)->_item->_type=='f';++i){
            if((*i)->_item->_name==name){
                cout<<"having existed a "<<name<<", please try another name"<<endl;
                return 0;
            }

        }
        node* dir=new node(this,name,'f');
        if(dir==nullptr)
            return 0;
        contents.push_front(dir);
        updateChangeTime();
        return 1;
    }
    //add Documents
    bool addDoc(const string &name,const size_t &size){
        if(name.size()==0)
            return 0;
        for(unsigned i(0);i<name.size();++i){
            if(name[i]==' '||name[i]=='\\'||name[i]=='/' ){
                cout<<"cannot use this name, please try another"<<endl;
                return 0;
            }
        }
        for(p_node i=contents.begin();i!=contents.end();++i){
            if(((*i)->_item->_type=='d')&&((*i)->_item->_name==name)){
                cout<<"having existed a "<<name<<", please try another name"<<endl;
                return 0;
            }
        }
        node* dir=new node(this,name,'d');
        if(dir==nullptr){
            cout<<"fail to apply for a document"<<endl;
            return 0;
        }
        dir->setSize(size);
        contents.push_back(dir);
        updateChangeTime();
        return 1;
    }
    //add storage
    bool addStorage(const size_t &size){
        if(_item->_type!='r')
            return 0;
        unsigned n=contents.size();
        string num;
        if(n<10)
            num+=(n+'0');
        else{
            cout<<"we only allow mounting at most 10 disks"<<endl;
            return 0;
        }
        //string sName("storage"+num);
        node *newStorage=new node(this,"storage"+num,'s');
        newStorage->_item->setSize(size);
        contents.push_back(newStorage);
        //_item->_name=("storage"+(n+'0'));
        return 1;
    }
    //set size but only for documents and storage
    bool setSize(const size_t &size){
        if(_item->_type=='f'||_item->_type=='r')
            return 0;
        _item->_size=size;
        updateChangeTime();
        return 1;
    }
    //get size, storage-> max size, other-> real size
    size_t size(){
        if(_item->_type=='s'||_item->_type=='d')
            return _item->_size;
        else if(_item->_type=='r'){
            p_node t=contents.begin();
            size_t s(0);
            while (t!=contents.end()) {
                s+=(*t)->_item->_size;
                ++t;
            }
            return s;
        }
        else{
            size_t s(0);
            p_node t=contents.begin();
            while (t!=contents.end()) {
                s+=(*t)->size();
                ++t;
            }
            return s;
        }
    }
    //get the storage at present
    node *storage(){
        node* s=this;
        while(s->_item->_type!='s'){
            s=s->_back;
        }
        return s;
    }
    //places have been used
    size_t used(){
        if(_item->_type!='s')
            exit(2);
        size_t used(0);
        auto it=contents.begin();
        while(it!=contents.end()){
            used+=(*it)->size();
            ++it;
        }
        return used;
    }

    void show(){
        cout<<setw(20)<<_item->_name<<setw(30)<<_item->get_changed_time()<<setw(10)<<size()<<setw(30)<<_item->get_created_time();
        if(_item->_type=='d')
            cout<<setw(10)<<"<file>";
        if(_item->_type=='f')
            cout<<setw(10)<<"<dir>";
        if(_item->_type=='s')
            cout<<setw(10)<<"<disk>";
        cout<<endl;
    }

    void showTree(string lines){
        cout<<lines<<"---"<<_item->_name<<endl;
        if(lines[lines.size()-1]=='+')
            lines[lines.size()-1]=' ';
        lines+="   |";
        auto it=contents.begin();
        while(it!=contents.end()){
            auto t=it;
            if((++t)==contents.end())
                lines[lines.size()-1]='+';
            if((*it)->_item->_type!='d'){
                (*it)->showTree(lines);
            }
            else
                cout<<lines+"---"<<(*it)->_item->_name<<endl;
            ++it;
        }
    }


};

#endif // ITEM_H
