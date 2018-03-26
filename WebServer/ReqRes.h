//
//  ReqRes.h
//  WebServer
//
//  Created by lavanya chennu on 24/03/18.
//  Copyright © 2018 com.bchennu. All rights reserved.
//

#ifndef ReqRes_h
#define ReqRes_h


struct Person{
    unsigned int id;
    char* name;
};

struct Persons{
    struct Person* person;
    int len;
};

struct HttpRequest{
     struct Person person;
    
};

struct HttpResponse{
    unsigned long id;
    
};


#endif /* ReqRes_h */
