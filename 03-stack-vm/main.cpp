#include <iostream>
using namespace std;

enum opcode{
    PUSH,
    ADD,
    PRINT,
    HALT
};

int main(){
    int stack[1024];
    int sp=0,ip=0,running=1,buffer;

    int prog[50];

    cout<<"Enter Program to run:\n";
    while(running){
        if(ip==48){
            cout<<"No further instructions possible.\n";
            prog[ip++]=HALT;
            break;
        }
        cout<<"1 for PUSH, 2 for ADD, 3 for PRINT, 4 for HALT: ";
        cin>>buffer;
        switch(buffer){
            case 1:
                if(ip==47){
                    cout<<"Can't store the instruction\n";
                    break;
                }
                prog[ip++]=PUSH;
                cout<<"Enter the number: ";
                cin>>prog[ip++];
                break;
            case 2:
                prog[ip++]=ADD;
                break;
            case 3:
                prog[ip++]=PRINT;
                break;
            case 4:
                prog[ip++]=HALT;
                running=0;
                break;
        }
    }

    ip=0;
    int currcode=prog[ip];
    running=1;

    while(running){
        if(sp==1023){
            cout<<"Memory is Full!\n";
            break;
        }
        currcode=prog[ip];
        switch(currcode){
            case PUSH:
                    buffer=prog[++ip];
                    stack[sp++]=buffer;
                break;
            case ADD:
                if(sp>1){
                    buffer=stack[--sp];
                    buffer+=stack[--sp];
                    stack[sp++]=buffer;
                }
                else{
                    cout<<"Not enough Values in stack!\n";
                }
                break;
            case PRINT:
                cout<<stack[sp-1]<<'\n';
                break;
            case HALT:
                running=0;
                break;
        }
        ++ip;
    }

    return 0;
}