

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

      
    while(1){

         
       
        
        const char* hello;  
        scanf("%s", hello);
        

        send(sock , hello , strlen(hello) , 0 ); 
        printf("--> Your message sent\n"); 

        if(strcmp(hello, "BYE") == 0){
            printf("\\\\ Close chat ////\n");
            break;
        }

        char buffer[1024] = {0}; 
        valread = read( sock , buffer, 1024); 
        printf("Server: %s\n",buffer );

        if(strcmp(buffer, "BYE") == 0){
            send(sock , "OK" , 2 , 0 );
            printf("----- Close chat -----\n");
            return 1;
        }

    }

    close(sock);
    return 0; 
} 