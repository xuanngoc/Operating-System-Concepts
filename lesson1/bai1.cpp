#include <dirent.h>
#include <iostream>
using namespace std;

int main()
{
    const char *a = "dirSample";
    DIR *dir = 0;
    dir = opendir(a);
    if(dir){
        cout<<"It works!\n\n";
    }
    struct dirent *pent = 0;
    
    while(pent = readdir(dir)){
        if(pent == 0){
            cout<<"Error\n";
        }
        cout<<pent -> d_name<<endl;
    }

}