//
//  redis-cache.h
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#ifndef redis_cache_h
#define redis_cache_h


#include <hiredis.h>

static const char *REDIS_HOST= "127.0.0.1";
static const int REDIS_PORT = 6379;
static const struct timeval REDIS_TIMEOUT = { 1, 500000 }; //1.5 secs

redisContext* create_connect_redis();

void free_connect_redis(redisContext* conn);

void set_cache_entry(const char* key,const char* val);

const char* get_cache_entry(const char* key);

void delete_cache_entry(const char* key);

long long int increment_counter(const char* counter);

long long int decrement_counter(const char* counter);

void add_to_array_entry(const char* arr_name,const char* name);

char** get_array_cache_entries(const char* arr_name);

#endif /* redis_cache_h */
