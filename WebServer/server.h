//
//  server.h
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include "ReqRes.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h> //system calls read and receive in this file
#include <stdbool.h>
#include "DB.h"


static const char* HTTP_REQ_PAYLOAD_DELIMITER="|";

#define PORT 9193
static const int NUM_OF_PARALLEL_CLIENTS=1;
static const int PAYLOAD_BUFFER_SIZE=1024;


char* serialize_response(struct HttpResponse*const response_string);

struct HttpRequest* deserialize_response(const char*const req_payload);


void start_server();


#endif /* server_h */
