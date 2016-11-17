#ifndef HASH_H
#define HASH_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
const unsigned int maxh=100;//length of hash list
class hashNum
{
public:
    hashNum();
    bool addUser(const string &number,const string&name, const string &address);
    bool check(const string&key);
    void showAll(){
        int j(0);
        for(unsigned i(0);i<maxh;++i){
            if(h_name[i]){
                node*p=h_name[i];
                while(p){
                    ++j;
                    cout<<setw(5)<<j<<setw(20)<<p->m_name<<setw(20)<<p->m_number<<setw(30)<<p->m_address<<endl;
                    p=p->name_next;
                }
            }
        }
    }

    void showAccordingName(){
        cout<<setw(5)<<"hash"<<setw(20)<<"names"<<endl;
        node*p(0);
        int count(0),conflict(0);
        for(unsigned i(0);i<maxh;++i){
            cout<<setw(5)<<i;
            if(h_name[i]){
                p=h_name[i];
                int k=0;
                while(p){
                    ++k;
                    ++count;
                    conflict+=k;
                    cout<<p->m_name<<' ';
                    p=p->name_next;
                }
            }
            cout<<endl;
        }
        cout<<"ASLsucc : "<<(float)conflict/count<<endl;
    }

    void showAccordingNum(){
        cout<<setw(5)<<"hash"<<setw(20)<<"names"<<endl;
        node*p(0);
        int count(0),conflict(0);
        for(unsigned i(0);i<maxh;++i){
            cout<<setw(5)<<i;
            if(h_num[i]){
                p=h_num[i];
                int k=0;
                while(p){
                    ++k;
                    ++count;
                    conflict+=k;
                    cout<<p->m_name<<' ';
                    p=p->num_next;
                }
            }
            cout<<endl;
        }
        cout<<"ASLsucc : "<<(float)conflict/count<<endl;
    }

    ~hashNum(){
        for(unsigned i(0);i<maxh;++i){
            if(h_name[i])
                delete h_name[i];
        }
    }
private:
    struct node{
        string m_number;
        string m_name;
        string m_address;
        node*name_next;
        node*num_next;
        node(const string &number,const string&name, const string &address):
            m_number(number),m_name(name),m_address(address),name_next(nullptr),num_next(nullptr){

        }
        ~node(){
            delete name_next;
        }
    };
    node *h_name[maxh];
    node *h_num[maxh];
    unsigned name_key(const string &name);
    unsigned num_key(const string &num);
    bool push_front(node *&rhs);
    bool search_name(const string& key);
    bool search_num(const string&key);


};


#endif // HASH_H
