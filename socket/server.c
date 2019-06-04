
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd; //Tao de listen
    int new_socket; // Tao khi accept connect
    int valread; 

    struct sockaddr_in serverAddress; 

    int opt = 1; 
    int addrlen = sizeof(serverAddress); 
    
    //char *hello = "Hello from server"; 
       
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // Create a new socket

    if (server_fd == 0) 
    { 
        printf("Khong the tao duoc socket.\n");
		return 1;
    }       
    

    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    serverAddress.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress))<0) 
    { 
        printf("Loi binding.\n");
        return 1;
    } 

    listen(server_fd, 5);
    
    printf("Server is listenning at %d\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr *)&serverAddress,  (socklen_t*)&addrlen);

    while(1){
        
        //Create a new socket to communicate with client
        char buffer[1024] = {0}; 
        valread = read( new_socket , buffer, 1024); 
        if(strcmp(buffer, "BYE") == 0){
            printf("Client: %s\n",buffer );
            printf("*** Close chat ***\n");
            return 1;
        }
        printf("Client: %s\n",buffer ); 

        const char* hello;
        scanf("%s", hello);
    
        send(new_socket , hello , strlen(hello) , 0 ); 
        printf("--> Your message sent\n"); 

        if(strcmp(hello, "BYE") == 0){
            printf("^^^ Close chat ^^^\n");
            close(new_socket);
            break;
        }

        
        
    } 
        
    close(server_fd);   
    
    return 0; 
} 