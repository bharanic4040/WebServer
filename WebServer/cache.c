//
//  cache.c
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//


#include "cache.h"
#include <stdlib.h>


redisContext* create_connect_redis(){
   
    redisContext* conn = redisConnectWithTimeout(REDIS_HOST, REDIS_PORT, REDIS_TIMEOUT);
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("Connection error: %s\n", conn->errstr);
            redisFree(conn);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(EXIT_FAILURE);
    }
    return conn;
}

void free_connect_redis(redisContext* conn){
     redisFree(conn);
}