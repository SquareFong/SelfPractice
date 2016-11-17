#include "hash.h"
#include<stdlib.h>
//#include<stdio.h>
hashNum::hashNum()
{
    unsigned i(maxh-1);
    do{
        h_name[i]=nullptr;
        h_num[i]=nullptr;
    }while(i--);
}

bool hashNum::addUser(const string &name, const string &number, const string &address){
    if(atoi(number.c_str())){
        node*newUser=new node(number,name,address);
        //hash for name
        unsigned temp(name_key(name));
        if(h_name[temp]==nullptr){
            h_name[temp]=newUser;
        }
        else{
            newUser->name_next=h_name[temp];
            h_name[temp]=newUser;
        }
        //hash for num
        temp=num_key(number);
        if(h_num[temp]==nullptr){
            h_num[temp]=newUser;
        }
        else{
            newUser->num_next=h_num[temp];
            h_num[temp]=newUser;
        }
        return 1;
    }
    else
        return 0;
}

bool hashNum::check(const string &key){
    bool num(true);
    for(int i(0);i<key.size();++i){
        if(key[i]<=' ')
            continue;
        if(key[i]<'0'||key[i]>'9'){
            num=false;
            break;
        }
    }
    if(num)
        return search_num(key);
    else
        return search_name(key);

}

unsigned hashNum::name_key(const string &name){
    unsigned temp(0);
    for(unsigned i(0);i<name.size();++i){
        temp*=7;
        temp+=(name[i]);
    }
    return temp%maxh;
}

unsigned hashNum::num_key(const string &num){
    unsigned temp(atoi(num.c_str()));
    unsigned result(0);
    unsigned mod(1000);
    /*if(mod!=100){
        mod=100;
    }
    ++mod;*/
    while(temp){
        result+=(temp%mod);
        temp/=mod;
    }
    if(result>maxh)
        result%=maxh;
    return result;
}

bool hashNum::search_name(const string &key){
    unsigned temp(name_key(key));
    bool check(false);
    if(h_name[temp]!=nullptr){
        node*p=h_name[temp];
        while(p){
            if(p->m_name==key){
                check=true;
                cout<<setw(20)<<p->m_name<<setw(20)<<p->m_number<<setw(30)<<p->m_address<<endl;
            }
            p=p->name_next;
        }
    }
    return check;
}

bool hashNum::search_num(const string &key){
    unsigned temp(num_key(key));
    bool check(false);
    if(h_num[temp]!=nullptr){
        node*p=h_num[temp];
        while(p){
            if(p->m_number==key){
                check=true;
                cout<<setw(20)<<p->m_name<<setw(20)<<p->m_number<<setw(30)<<p->m_address<<endl;
            }
            p=p->num_next;
        }
    }
    return check;
}
