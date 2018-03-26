//
//  main.c
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.

// http://www.programering.com/a/MzNxcjNwATg.html
//redis-server /usr/local/etc/redis.conf  and redis-cli ping

/*
 To have launchd start postgresql now and restart at login:
 brew services start postgresql
 Or, if you don't want/need a background service you can just run:
 pg_ctl -D /usr/local/var/postgres start
 
 lavanya/lavanya are the credentials
 
 psql postgres -U lavanya
 */

#include <stdio.h>
#include "server.h"
#include "redis-cache.h"

struct Emp{
    char* name;
    int id;
};
struct Emps{
    struct Emp* emp;
    int len;
};
int main(int argc, const char * argv[]) {
    
    //start_server();
    
    struct Persons persons=fetch_records(NULL);
   /*int len=persons.len;
    int j=0;
    while(j<len){
        printf("test > %d- %s\n",persons.person->id,persons.person->name);
        persons.person++;
        j++;
    }*/
    return 0;
}
