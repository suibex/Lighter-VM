#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "display.h"
using namespace std;
/*

    so first order of business 
    lets first setup CPU, then i will do that and create a BIOS 
    and create a bootstrap and display

*/
int main(int argc,char *argv[]){
    if(argc<2){
        cout<<"Provide the correct .bin file to boot."<<endl;
        exit(1);
    }
    //lets just first create CPU and then i will mix it with display
    Display *disp = new Display();
    disp->MainWindow(argv[1]);
}