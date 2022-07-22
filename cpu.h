#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#define DEBUG 1

using namespace std;


class CPU{

    
    public:
        int CPU_NODE=0;
       //ok this CPU is not implemented fully , but it works for basic stuff,and most important ,for priting,moving sub,add! (was to lazy to do everything haha)
       //i just want to see if it is possible to actually do this
        vector<signed int> AX = vector<signed int>(2);
        vector<signed int> BX= vector<signed int>(2);
        vector<signed int> CX= vector<signed int>(2);
        vector<signed int> DX= vector<signed int>(2);
        signed int F =0;
        signed int BP = 0;
        signed int SP = 0;
        signed int IP=0;
        signed int CS = 0;
        signed int DS = 0;
        signed int SS=0;
        signed int ES = 0;
        signed int SI = 0;
        signed int Di=0;
        vector<signed int>STACK;
        vector<string>hex_data;
          
        void fetch(string filename){
            unsigned char b[2];
            FILE *a = fopen(filename.c_str(),"r");
            while(true){
                int re = fread(b,sizeof(unsigned char),1,a);
                if(re<=0){
                    break;
                }
                char *bebe = (char*)malloc(sizeof(unsigned char));
                sprintf(bebe,"%02x",b[0]);
                hex_data.push_back(bebe);
                free(bebe);

            }
        }

        void debug(){
            cout<<"================ Debug mode ON ================"<<endl;
            cout<<"AX=AH:"<<AX[0]<< " AL:"<<AX[1]<<endl;
            cout<<"BX=BH:"<<BX[0]<< " BL:"<<BX[1]<<endl;
            cout<<"CX=CH:"<<CX[0]<< " CL:"<<CX[1]<<endl;
            cout<<"DX=DH:"<<DX[0]<< " DL:"<<DX[1]<<endl;
            cout<<"IP:"<<IP<<" SP:"<<SP<<" BP:"<<BP<<" FLAG:"<<F<<endl;
        }       
        void decode_execute(int i){
           
            
                 #ifdef DEBUG
                    debug();
                #endif
                string instr = hex_data[i];
                //MOV NUMS
                bool executed =false;

                if(instr == "b8"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    AX[0] = num;
                    executed=true;
                
                }
                if(instr == "b4"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    AX[0] = num;
                    executed=true;
                }
                if(instr == "b0"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    AX[1] = num;
                    executed=true;
                }

                if(instr == "bb"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    BX[0] = num;
                    executed=true;
                }
                if(instr == "b7"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    BX[0] = num;
                    executed=true;
                }
                if(instr == "b3"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    BX[1] = num;
                    executed=true;
                }                
                if(instr == "b9"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    CX[0] = num;
                    executed=true;
                }
                if(instr == "b5"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    CX[0] = num;
                executed=true;
                }
                if(instr == "b1"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    CX[1] = num;
                executed=true;
                }
                if(instr == "ba"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    DX[0] = num;
                executed=true;
                }
                if(instr == "b6"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    DX[0] = num;
                    executed=true;
                }
                if(instr == "b2"){
                    int num =0;
                    ss.clear();
                    ss<<hex_data[i+1];
                    ss>>hex>>num;                
                    DX[1] = num;
                    executed=true;
                }
                //END OF MOV NUMS
                
                //begin of mov regs
                if(instr == "89"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[0] = BX[0];
                    }
                    if(combo == "d1"){
                        CX[0]=DX[0];
                    }
                    if(combo == "ca"){
                        DX[0]=CX[0];
                    }
                    if(combo == "e5"){
                        BP = SP;
                    }
                    if(combo == "ec"){
                        SP=BP;
                    }
                    if(combo == "c3"){
                        BX[0] = AX[0];
                    }
                    executed=true;
                }


                if(instr == "29"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[0] -= BX[0];
                    }
                    if(combo == "d1"){
                        CX[0]-=DX[0];
                    }
                    if(combo == "ca"){
                        DX[0]-=CX[0];
                    }
                    if(combo == "e5"){
                        BP -= SP;
                    }
                    if(combo == "ec"){
                        SP-=BP;
                    }
                    if(combo == "c3"){
                        BX[0] -= AX[0];
                    }
                    executed=true;
                }

                if(instr == "01"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[0] += BX[0];
                    }
                    if(combo == "d1"){
                        CX[0]+=DX[0];
                    }
                    if(combo == "ca"){
                        DX[0]+=CX[0];
                    }
                    if(combo == "e5"){
                        BP += SP;
                    }
                    if(combo == "ec"){
                        SP+=BP;
                    }
                    if(combo == "c3"){
                        BX[0] += AX[0];
                    }
                    executed=true;
                }

                if(instr == "39"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        if(AX[0]>BX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "d1"){
                     
                        if(DX[0]>CX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "ca"){
                        //CX[0]+=DX[0];
                        if(DX[0]>CX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "e5"){
                        //SP += BP;
                        if(BP>SP){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "ec"){
                        //BP+=SP;
                        if(SP>BP){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "c3"){
                        //AX[0] += BX[0];
                        if(BX[0]>AX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    executed=true;
                }

                if(instr == "55"){
                    STACK.insert(STACK.begin(),BP);
                    executed=true;
                }
                if(instr =="88"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[1] = BX[1];
                    }
                    if(combo == "fc"){
                        AX[0] = BX[0];
                    }
                    
                    if(combo == "c4"){
                        AX[0] = AX[1];
                    }
                    if(combo == "e0"){
                        AX[1] = AX[0];
                    }



                    if(combo == "f5"){
                        CX[0]=DX[0];
                    }
                    if(combo == "d1"){
                        CX[1]=DX[1];
                    }
                    if(combo == "ca"){
                        DX[1]=CX[1];
                    }
                    if(combo == "ee"){
                        DX[0]=CX[0];
                    }
                    if(combo == "e5"){
                        BP = SP;
                    }
                    if(combo == "ec"){
                        SP=BP;
                    }
                    if(combo == "c3"){
                        BX[1] = AX[1];
                    }
                    if(combo == "e7"){
                        BX[0] = AX[0];
                    }
                    executed=true;
                }

                if(instr =="28"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[1] -= BX[1];
                    }
                    if(combo == "fc"){
                        AX[0] -= BX[0];
                    }
                    if(combo == "f5"){
                        CX[0] -= DX[0];
                    }
                    if(combo == "d1"){
                        CX[1]-=DX[1];
                    }
                    if(combo == "ca"){
                        DX[1]-=CX[1];
                    }
                    if(combo == "ee"){
                        DX[0]-=CX[0];
                    }
                    if(combo == "e5"){
                        BP -= SP;
                    }
                    if(combo == "ec"){
                        SP-=BP;
                    }
                    if(combo == "c3"){
                        BX[1] -= AX[1];
                    }
                    if(combo == "e7"){
                        BX[0] -= AX[0];
                    }
                    executed=true;
                }

                if(instr =="00"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                        AX[1] += BX[1];
                    }
                    if(combo == "fc"){
                        AX[0] += BX[0];
                    }
                    if(combo == "f5"){
                        CX[0] += DX[0];
                    }
                    if(combo == "d1"){
                        CX[1] += DX[1];
                    }
                    if(combo == "ca"){
                        DX[1] += CX[1];
                    }
                    if(combo == "ee"){
                        DX[0] += CX[0];
                    }
                    if(combo == "e5"){
                        BP += SP;
                    }
                    if(combo == "ec"){
                        SP+=BP;
                    }
                    if(combo == "c3"){
                        BX[1] += AX[1];
                    }
                    if(combo == "e7"){
                        BX[0] += AX[0];
                    }
                    executed=true;
                }

                if(instr =="38"){
                    string combo = hex_data[i+1];
                    if(combo == "d8"){
                       // BX[1] += AX[1];
                        if(AX[1]>BX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "fc"){
                     //   BX[0] += AX[0];
                    
                        if(AX[0]>BX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    
                    }
                    if(combo == "f5"){
                     //   DX[0] += CX[0];
                        if(CX[1]>DX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "d1"){
                     //   DX[1] += CX[1];
                     if(CX[1]>DX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "ca"){
                     //   CX[1] += DX[1];
                        if(DX[1]>CX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "ee"){
                     //   CX[0] += DX[0];
                        if(DX[1]>CX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "e5"){
                     //   SP += BP;
                        if(BP>SP){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "ec"){
                     //   BP+=SP;
                         if(SP>BP){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "c3"){
                     //   AX[1] += BX[1];
                        if(BX[1]>AX[1]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    if(combo == "e7"){
                     //   AX[0] += BX[0];
                        if(BX[0]>AX[0]){
                            F=1;
                        }
                        else{
                            F=-1;
                        }
                    }
                    executed=true;
                }
                //TODO: implement move,sub,add for low-high regs

                if(instr == "f4"){
                    //can't figure it out for now (until i get other stuff working)

                    cout<<"Halting CPU."<<endl;
                    cout<<"\033[1;33mwarning:\033[0m CPU HALT CALLED BUT NOT IMPLEMENTED CORRECTLY!"<<endl;
                    CPU_NODE = 23;
                    executed=true;
                }
                if(instr == "cd"){
                    string code = hex_data[i+1];
                    if(code == "10"){
                        CPU_NODE=10;

                    }
                    executed=true;
                }
                //end of mov regs
                if(executed==true){
                    IP++;
                }

            }   

        
    private:
        stringstream ss;
     
    
};