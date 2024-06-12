# Browser Controller
BrowserController is a class representing the database window of OsiriX. It provides some functionality for accessing
user study/series selection, and a tool for data import.

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 5-7)"}
----8<----
protos/types.proto:5:7
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc BrowserControllerXyz (BrowserControllerXyzRequest) returns (BrowserControllerXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.BrowserControllerXyz(request) # (1)
```

1. `response` is a  `BrowserControllerXyzResponse` class, and `request` a `BrowserControllerXyzRequest` class.

``` { .c++ title="osirix.proto (lines 128-131)"}
----8<----
protos/osirix.proto:128:131
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message BrowserControllerXyzResponse{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

has attributes accessed in Python (for example) using syntax
``` { .py}
x1 = response.arg1
x2 = response.arg2
...
```

``` { .c++ title="browsercontroller.proto (lines 9-23)"}
----8<----
protos/browsercontroller.proto:9:23
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message BrowserControllerXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import browsercontroller_pb2

request = browsercontroller_pb2.BrowserControllerXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="browsercontroller.proto (lines 26-)"}
----8<----
protos/browsercontroller.proto:26:
----8<----
```