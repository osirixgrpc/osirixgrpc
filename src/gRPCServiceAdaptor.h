//
//  ServiceAdaptor.h
//  pyOsiriXII
//
//  Created by Richard Holbrey on 01/12/2020.
//

@class NSLock, NSString;

/** \brief ServiceAdaptor
        Communication object between server and plugin code (which usually has to be on the main thread).
 */
struct gRPCServiceAdaptor {

    void* manager;    ///< Initialized and owned by plugin represented by this member, which, in use,
    
    NSLock* lock;  ///< Mutex, owned by plugin, used to control access to Request & Response

    NSString* address;  ///< Initialized by plugin

    const void* request;  ///<  C++ server request type (based on call type, owned by Server)
    void* response;       ///<  C++ server response  type (based on call type, owned by Server)
};


