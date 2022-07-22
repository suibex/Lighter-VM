#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "cpu.h"

using namespace std;



class Display{


    public:
      

        
        bool STARTING_BOOT =true;
        int pressed_bios=0;
        int NODE=0;
        vector<string>VIDEO_MEM;
        int BOOTABLE = false;
        bool BIOS_ACCESS=false;
        SDL_Renderer *renderer;
        SDL_Window *wind;
      
        void BootSplash(){
            time_t current_time;
            struct tm *loc_time;
            BIOS_ACCESS=true;
            STARTING_BOOT=true; 
            time(&current_time);

            loc_time= localtime(&current_time);

            int h = loc_time->tm_hour;
            int m = loc_time->tm_min;
            string time = to_string(h)+":"+to_string(m);
            SDL_Color clr = {0,0,0};
            SDL_Color txtc = {255,255,255};
          
            
            SDL_RenderClear(renderer);
            PrintText("",10,450,15,clr);
            //SDL_RenderClear(renderer);

            PrintText("L",130,30,18,txtc);
            PrintText("hello",200,80,18,txtc);
            SDL_RenderClear(renderer);
            //write here
            PrintText("",100,50,18,txtc);
            SDL_RenderClear(renderer);
            PrintText("Exit BIOS by pressing CTRL.",100,90,18,txtc);
            PrintText("Exit BIOS by pressing CTRL.",100,90,18,txtc);

            PrintText("No real settings here, just me flexing.",100,70,18,txtc);
            PrintText("No real settings here, just me flexing.",100,70,18,txtc);

            PrintText(time,20,440,18,txtc);
            PrintText(time,20,440,18,txtc);

            PrintText("BIOS Setup Utility Copyright (C) nitrodegen 2022.",40,30,22,txtc);
             
            //PrintText("welcome",100,50,18,txtc);
            
            //SDL_RenderClear(rnderer);

            //use when exiting bios
            //BIOS_ACCESS=false;
            //STARTING_BOOT=false; 
            
            
        }


        void PrintText(string data,int x, int y,int size,SDL_Color color){
            int w,h;
            TTF_Font *sans = TTF_OpenFont("./font.ttf",size);
       
            SDL_Surface *text = TTF_RenderText_Solid(sans,data.c_str(),color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,text);
            SDL_QueryTexture(texture,NULL,NULL,&w,&h);
            SDL_Rect dstrect = { x,y, w, h };
            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(text);

        }

        void ClearScreen(){
            SDL_Surface *surf = SDL_GetWindowSurface(wind);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surf);

        }

        bool CheckVIDEO(string ch,int y){
            int corr=0;
            for(int i =0;i<VIDEO_MEM.size();i++){
                string tr = VIDEO_MEM[i];
                string chh = tr.substr(0,tr.find(":"));
                string ystr = tr.substr(tr.find(":")+1);
                int y1= stoi(ystr);
                if(y1 != y){
                    corr++;
                }
            }
            cout<<corr<<endl;
            if(corr>=VIDEO_MEM.size()){
                return false;
            }
            else{
                return true;
            }
        }
        void MainWindow(string filename){
            CPU *cpu = new CPU();
            cpu->fetch(filename);
            int w,h;
            SDL_Init(SDL_INIT_VIDEO);
          
            	
            TTF_Init();

            wind = SDL_CreateWindow("Lighter (x86 16-bit)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,0);
            	
            renderer = SDL_CreateRenderer(wind, 1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);        
        
            SDL_Event evn ;
            int k =0;
            while(true){
                if(pressed_bios >=4 && BIOS_ACCESS==true){
                    cout<<"BIOS Starting up..."<<endl;
                    BootSplash();

                    pressed_bios=0;
                }   
               
                while(SDL_PollEvent(&evn)){
                    if(evn.type == SDL_QUIT){
                        
                        SDL_DestroyWindow(wind);
                        SDL_Quit();
                        exit(1);
                    }
                    if(evn.type== SDL_KEYDOWN){
                            
                            if(evn.key.keysym.sym ==SDLK_SLASH ){
                                pressed_bios++;
                                BIOS_ACCESS=true;
                            }
                            if(evn.key.keysym.sym == SDLK_RETURN){
                                
                                STARTING_BOOT=false;
                            }
                            if(evn.key.keysym.sym == SDLK_LCTRL){
                                SDL_Color clr={0,0,0};
                                SDL_RenderClear(renderer);
                                //write here
                                PrintText("",100,50,18,clr);
                                SDL_RenderClear(renderer);
                                BIOS_ACCESS=false;
                                STARTING_BOOT=true; 
                            }

                    }
                }
                if(STARTING_BOOT==true && BIOS_ACCESS==false){
                     
                        SDL_Color color  = {255,255,255};
                        PrintText("Lighter_VM BIOS v0.001pa 18 July 22.",10,10,17,color);
                        PrintText("Copyright (C) 2022 , nitrodegen",10,30,15,color);
                        PrintText("Note: this is really basic VM, proof of concept.",10,50,15,color);
                        PrintText("Boot from '"+filename+"' by pressing Enter.",10,80,15,color);
                        PrintText("Press '/' to Enter BIOS",10,450,15,color);

                }
                if(STARTING_BOOT==false ){
                   
                    if(BOOTABLE==false){
                        for(int i =0;i<cpu->hex_data.size();i++){
                            string tte= cpu->hex_data[i];
                            if(tte=="55"){
                                BOOTABLE=true;
                                break;
                            }
                        }
                    }
                
                    if(NODE != 23 && BOOTABLE == true){
                        SDL_Color color  = {0,0,0};
                        STARTING_BOOT=false;
                        BOOTABLE=true;
                        if(NODE!=10){
                            SDL_RenderClear(renderer);
                            PrintText("",10,450,15,color);
                            SDL_RenderClear(renderer);
                        }

                        if(VIDEO_MEM.size()>0){
                            for(int z = 0;z<VIDEO_MEM.size();z++){
                                SDL_Color ourc  = {255,255,255};
                                string tr = VIDEO_MEM[z];
                                string chh = tr.substr(0,tr.find(":"));
                                string ystr = tr.substr(tr.find(":")+1);
                                int y = stoi(ystr);
                                //cout<<"DATA:"<<chh<<":"<<y<<":"<<VIDEO_MEM.size()<<endl;
                                PrintText(chh,y,y,17,ourc);
                            }
                        }
                       
                        cpu->decode_execute(k);
                        NODE = cpu->CPU_NODE;
                        if(NODE == 10){
                           
                            int type = cpu->AX[0];
                            int what = cpu->AX[1];
                            static int clrs = cpu->BX[0];
                            int y_page = cpu->BX[1];
                           // cout<<type<<":"<<what<<":"<<clrs<<":"<<y_page<<endl;
                            
                            if(type == 0xe){
                                string cc;
                                cc+=(char)what;
                                if(clrs ==0xe){
                                    SDL_Color ourc  = {255,255,255};
                                    string dat =cc+":"+to_string(y_page);
                                    bool exists = CheckVIDEO(cc,y_page);

                                    if(exists==false){
                                         VIDEO_MEM.push_back(dat);
                                    }
                                    //PrintText(cc,y_page+2,y_page+2,14,ourc);   
                                    cout<<"\033[1;33mSDL2 Event\033[0m:Printing char on Screen."<<endl;

                                }
//                                NODE=0;

                            } 

                        }
                        if(k<=cpu->hex_data.size()){
                            k++;
                        }
                        //SDL_Delay(10);
                    }
                    if(BOOTABLE==false){
                        SDL_Color ourc  = {255,255,255};
                        SDL_RenderClear(renderer);
                        PrintText("Disc not bootable. CPU Halted.",10,450,15,ourc);
                    }
                }
                
               
            }
           
        
        }
        
    
};