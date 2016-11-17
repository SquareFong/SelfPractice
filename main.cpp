
#include "item.h"
#include "filemanage.h"
#include "stdlib.h"
#include <map>
using namespace std;

map<string,int> operations;

void initOperations(){
    operations.insert(pair<string,int>("ls",1));
    operations.insert(pair<string,int>("mkdir",2));
    operations.insert(pair<string,int>("newfile",3));
    operations.insert(pair<string,int>("mount",4));
    operations.insert(pair<string,int>("unmount",5));
    operations.insert(pair<string,int>("rm",6));
    operations.insert(pair<string,int>("search",7));
    operations.insert(pair<string,int>("resize",8));
    operations.insert(pair<string,int>("cd",9));
    operations.insert(pair<string,int>("tree",10));
    operations.insert(pair<string,int>("exit",100));
}

void test(tree&t){
    t.mount(1024);
    t.mount(2048);
    t.mount(2048);
    t.cd("storage1");
    t.mkdir("home");
    t.cd("home");
    t.mkdir("square");
    t.cd("square");
    t.mkdir("Videos");
    t.mkdir("Pictures");
    t.mkdir("Music");
    t.mkdir("Downloads");
    t.mkdir("Documents");
    t.mkdir("Desktop");
    t.cd("Documents");
    t.mkdir("Hello");
    t.mkdir("test");
    t.cd("test");
    t.newfile("test.cpp",1);
    t.newfile("test.h",100);
    t.newfile("test.o",100);
    t.cd("root");
    //t.showTree();
}

int main()
{
    tree files;
    string comand,info;
    initOperations();
    test(files);
    cout<<files.getDir()<<":~$ ";
    bool c(true);
    while(cin>>comand){
       int oper=operations[comand];
       switch (oper) {
       case 1:files.ls();break;
       case 2:cin>>info;files.mkdir(info);break;
       case 3:{ 
                size_t size;
                cin>>info;
                cin>>size;
                files.newfile(info,size);break;
       }
       case 4:cin>>info;files.mount(atoi(info.c_str()));break;
       case 5:cin>>info;files.unmount(info);break;
       case 6:cin>>info;files.rm(info);break;
       case 7:cin>>info;files.search(info);break;
       case 8:cin>>info;files.resize(atoi(info.c_str()));break;
       case 9:cin>>info;files.cd(info);break;
       case 10:files.showTree();break;
       case 100:c=false;break;
       default:
           cout<<comand<<':'<<"not finding this command"<<endl;
           break;
       }
       if(c)
           cout<<files.getDir()<<":~$ ";
       else
           break;
    }
    return 0;
}
