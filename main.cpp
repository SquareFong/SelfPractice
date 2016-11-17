#include "hash.h"

string IntToStr(int rhs){
    string temp;
    while(rhs){
        temp+=(rhs%10+'0');
        rhs/=10;
    }
    return temp;
}

string IntToName(int rhs){
    string temp;
    if(rhs<0)
        rhs*=(-1);
    while(rhs){
        temp+=(rhs%10+'a');
        rhs/=10;
    }
    return temp;
}

void test(hashNum &note){
    /*
    note.addUser("zhangsan","123456","wuhan");
    note.addUser("lisi","10000","wuhan");
    note.addUser("wanger","10086","wuhan");
    note.addUser("sa","1008633","wuhan");
    note.addUser("zhang","10086","wuhan");
    note.addUser("san","10010","wuhan");
    note.addUser("lisi","1654321","wuhan");
    note.addUser("zhangsan","123456","wuhan");*/
    for(int i(0);i<1000;++i){
        srand(i);
        unsigned t(rand());
        t%=10000;
        //char tc('a'+i%10);
        string s("hubei ");
        char ta('a'+t%26);
        string addr(s+ta);
        note.addUser(IntToName(t),IntToStr(t),addr);

    }
}

int main()
{
    hashNum notebook;
    test(notebook);
    string command;
    string name,num,addr;
    notebook.showAccordingNum();
    cout<<"this is a note book to store user information of name, phone number and address\nplease use add to add info,and use search to find user\nuse show to show all the info"<<endl;
    cout<<">>>";
    while(cin>>command){
        if(command=="add"){
            cout<<"please input name,phone number and address"<<endl;
            cout<<">>>";
            cin>>name>>num>>addr;
            if(!(notebook.addUser(name,num,addr)))
                cout<<"input fail, please check your information,and use add again"<<endl;
            else
                cout<<"success"<<endl;
        }
        else if(command=="search"){
            cout<<"please input name or address"<<endl;
            cout<<">>>";
            cin>>command;
            if(!(notebook.check(command)))
                cout<<"no such user"<<endl;

        }
        else if(command=="show"){
            notebook.showAccordingName();
        }
        else if(command=="exit")
            break;
        else
            cout<<"no such command, try again"<<endl;
        cout<<">>>";
    }
    return 0;
}
