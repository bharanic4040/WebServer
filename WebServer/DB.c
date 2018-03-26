//
//  DB.c
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#include "DB.h"
#include <stdlib.h>
#include "redis-cache.h"
#include <string.h>

long persist(struct HttpRequest* http_request){
    printf("Request payload logged: %s \n",http_request->person.name);
    return http_request->person.id;
}


