#include <dirent.h>
#include <iostream>
using namespace std;

int main()
{
    const char *rootDir = "."; // I will check this directiry
    DIR *dir = 0; //null
    dir = opendir(rootDir);
    /* if(dir){
        cout<<"It works!\n\n";
    } */
    struct dirent *pent = 0;
    
    cout<<"List directories: \n";
    while(pent = readdir(dir)){
        if(pent == 0){
            cout<<"Error\n";
        }
        cout<<pent -> d_name<<endl;
    }

}