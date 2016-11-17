#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include "item.h"
#include<queue>
using namespace std;

class tree{
    node root;
    node *now;
    string dir;
    void count(){
        unsigned filesNum(0);
        unsigned docNum(0);
        queue<node*> Q;
        node *temp=now;
        Q.push(now);
        while(Q.size()){
            temp=Q.front();
            Q.pop();
            auto it=temp->contents.begin();
            while(it!=temp->contents.end()){
                if((*it)->_item->_type=='f')
                    ++filesNum;
                else
                    ++docNum;
                Q.push(*it);
                ++it;
            }
        }
        if(filesNum>1)
            cout<<filesNum<<" directories, ";
        else
            cout<<filesNum<<" directory, ";
        if(docNum>1)
            cout<<docNum<<" files\n";
        else
            cout<<docNum<<" file\n";

    }
public:
    tree():root(NULL,"root",'r'),now(&root),dir("/root/"){}
    ~tree(){
        while(!root.contents.empty()){
            delete (*root.contents.begin());
            root.contents.pop_front();
        }
    }

    string getDir(){
        return dir;
    }

    bool mkdir(const string &name){
        if(now->_item->_type=='r'){
            cout<<"cannot make directory here"<<endl;
            return 0;
        }
        if(now->mkDir(name))
            return 1;
        else
            return 0;
    }

    bool newfile(const string &name,const size_t &size=0){
        if(now->_item->_type=='r')
            return 0;
        size_t unused(0);
        unused=(now->storage()->size() - now->storage()->used());
        if(size>unused){
            cout<<"not enough storage"<<endl;
            return 0;
        }
        if(now->addDoc(name,size))
            return 1;
        else
            return 0;
    }

    bool mount(const size_t &size){
        if(root.addStorage(size))
            return 1;
        else
            return 0;
    }

    bool resize(const size_t &size){
        if(now->setSize(size))
            return 1;
        else
            return 0;
    }

    bool unmount(const string &name){
        if(now->_item->_type!='r'){
            cout<<"cannot use unmount here\n";
            return 0;
        }
        auto del(root.contents.begin());
        while(del!=root.contents.end()){
            if((*del)->_item->_name==name){
                delete (*del);
                root.contents.erase(del);
                return 1;
            }
            ++del;
        }
        cout<<"no such storage"<<endl;
        return 0;
    }

    bool ls(){
        auto show=now->contents.begin();
        cout<<setw(20)<<"name"<<setw(30)<<"last changed time "<<setw(10)<<"size(KB)"<<setw(30)<<"created time  "<<endl;
        while(show!=now->contents.end()){
            (*show)->show();
            ++show;
        }
        return 1;
    }

    bool cd(const string &name){
        if(name==".."){
            if(now->_item->_type=='r'){
                cout<<"not being able to return to the directory you were in previously"<<endl;
                return 0;
            }
            now=now->_back;
            int i(this->dir.size()-2);
            for(;i>=0;--i)
            {
                if((this->dir)[i]=='/')
                    break;
            }
            this->dir.resize(i+1);
            return 1;
        }
        if(name=="root"){
            now=&root;
            dir="/root/";
            return 1;
        }
        auto dir(now->contents.begin());
        while(dir!=now->contents.end()){
            if((*dir)->_item->_name==name){
                if((*dir)->_item->_type=='d'){
                    cout<<"It's impossible to open a document with command: cd"<<endl;
                    return 0;
                }
                now=(*dir);
                (this->dir)+=(now->_item->_name+'/');
                return 1;
            }
            ++dir;
        }
        cout<<"no such file"<<endl;
        return 0;
    }

    bool rm(const string &name){
        if(now->_item->_type=='r'){
            cout<<"please use unmount here"<<endl;
            return 0;
        }
        auto dir(now->contents.begin());
        while(dir!=now->contents.end()){
            if((*dir)->_item->_name==name)
            {
                delete (*dir);
                now->contents.erase(dir);
                return 1;
            }
            ++dir;
        }
        cout<<"no such file or directory here\n";
        return 0;
    }

    bool search(const string &name){
        bool found(0);
        auto dir(now->contents.begin());
        while(dir!=now->contents.end()){
            string fName((*dir)->_item->_name);
            for(unsigned i(0);i<fName.size();++i){
                if(name[0]==fName[i]){
                    unsigned j(i);
                    unsigned t(0);
                    for(;j<fName.size()&&t<name.size();++j,++t){
                        if(name[t]!=fName[j])
                            break;
                    }
                    if(t==name.size()){
                        (*dir)->show();
                        break;
                        found=1;
                    }

                }
            }
            ++dir;
        }
        return found;
    }

    void showTree(){
        string lines("|");
        cout<<"."<<endl;
        auto it=now->contents.begin();
        while(it!=now->contents.end()){
            auto t=it;
            if((++t)==now->contents.end())
                lines[lines.size()-1]='+';
            if((*it)->_item->_type!='d'){
                (*it)->showTree(lines);
            }
            else
                cout<<lines+"---"<<(*it)->_item->_name<<endl;
            ++it;
        }
        if(now->_item->_type!='r'){
            cout<<endl;
            count();
        }
    }

};


#endif // FILEMANAGE_H
