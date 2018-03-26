//
//  server.c
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#include "server.h"
#include <stdlib.h>
#include <string.h>

void parse_request(const char*const req_payload,struct Person* person){
    char* token;
    token=strtok(req_payload,HTTP_REQ_PAYLOAD_DELIMITER);
    person->id=atoi(token);
    if( token != NULL ) {
        token = strtok(NULL,HTTP_REQ_PAYLOAD_DELIMITER);
        person->name=token;
    }

}


char* serialize_response(struct HttpResponse*const response){
    char* response_string=(char*)malloc(31*sizeof(char));
    char buffer[10];
    strcpy(response_string, "From server > ");
    sprintf(buffer, "%lu", response->id);
    strcat(response_string, buffer);
    return response_string;
}

struct HttpRequest* deserialize_request(const char*const req_payload){
    struct HttpRequest* request=(struct HttpRequest*)malloc(sizeof(struct HttpRequest));
    if(request==NULL){
        perror("Failed to allocate memory for HttpRequest, exiting.");
        exit(EXIT_FAILURE);
    }
    struct Person person;
    //parse id|name from request
    parse_request(req_payload,&person);
    request->person=person;

    return request;
}

//send response back to client
static void send_to_client(const int client_sock_fd){
    printf("client connected with id: %d\n",client_sock_fd);
    char buffer[PAYLOAD_BUFFER_SIZE]={0};
    
    read( client_sock_fd , buffer, PAYLOAD_BUFFER_SIZE);
    printf("Received from client - %s\n",buffer );
    struct HttpRequest* http_request=deserialize_request(buffer);
    long uuid=persist(http_request);
    free(http_request);
    http_request=NULL;
    struct HttpResponse response={uuid};
    char* response_string=serialize_response(&response);
    send(client_sock_fd , response_string, strlen(response_string) , 0 );
    free(response_string);
    printf("message sent\n on id: %d\n",client_sock_fd);
    close(client_sock_fd);
}

void start_server()
{
    
    int server_fd,client_sock_fd;
    struct sockaddr_in address;
    struct sockaddr_in client_address;
    memset(&address, 0, sizeof(address));
    socklen_t client_addr_len;
    
    
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("Socket creation failed on server");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    
    if((bind(server_fd,(struct sockaddr*)&address,sizeof(address)))<0)
    {
        perror(">>> Bind to port failed on server");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd, NUM_OF_PARALLEL_CLIENTS)<0)
    {
        perror(">>> Listen failed in server");
        exit(EXIT_FAILURE);
        
    }
    printf(">>> Waiting for client connections....\n");
    while(true)
    {
        
        if ((client_sock_fd = accept(server_fd, (struct sockaddr *)&client_address,&client_addr_len))<0)
        {
            perror("accept of client failed");
            exit(EXIT_FAILURE);
        }
        send_to_client(client_sock_fd);
    }
    
}






