//
//  redis-cache.c
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#include "redis-cache.h"
#include <stdlib.h>
#include <string.h>

redisContext* create_connect_redis()
{
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


void set_cache_entry(const char* key,const char* val){
    if(key==NULL){
        printf("Key is null here %s. so ,set key not invoked.\n",key);
        return;
    }
    redisContext* conn=create_connect_redis();
    redisReply *reply=redisCommand(conn, "SET %s %s",key,val);
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);
    free_connect_redis(conn);
    
}

const char* get_cache_entry(const char* key){
    
    redisContext* conn=create_connect_redis();
    char tmp[20]="GET ";
    strcat(tmp,key);
    redisReply *reply = redisCommand(conn,tmp);
    printf("GET %s: %s\n", key,reply->str);
    if(reply->str==NULL){
        return NULL;
    }
    char* val=(char*)malloc(strlen(reply->str)+1);
    strcpy(val,reply->str);
    freeReplyObject(reply);
    free_connect_redis(conn);
    return val;
}

void delete_cache_entry(const char* key){
    
    redisContext* conn=create_connect_redis();
    char tmp[20]="DEL ";
    strcat(tmp,key);
    redisReply *reply = redisCommand(conn,tmp);
    freeReplyObject(reply);
    free_connect_redis(conn);

}

long long int increment_counter(const char* counter){
   
    redisContext* conn=create_connect_redis();
    char tmp[20]="INCR ";
    strcat(tmp,counter);
    redisReply *reply = redisCommand(conn,tmp);
    printf("INCR %s: %lld\n", counter,reply->integer);
    long long int inc=reply->integer;
    freeReplyObject(reply);
    free_connect_redis(conn);
    return inc;
}

long long int decrement_counter(const char* counter){
    
    redisContext* conn=create_connect_redis();
    char tmp[20]="DECR ";
    strcat(tmp,counter);
    redisReply *reply = redisCommand(conn,tmp);
    printf("DECR %s: %lld\n", counter,reply->integer);
    long long int inc=reply->integer;
    freeReplyObject(reply);
    free_connect_redis(conn);
    return inc;
}

void add_to_array_entry(const char* arr_name,const char* name){
  
        redisContext* conn=create_connect_redis();
        redisReply *reply = redisCommand(conn,"RPUSH %s %s",arr_name,name);
        freeReplyObject(reply);
        free_connect_redis(conn);
}

