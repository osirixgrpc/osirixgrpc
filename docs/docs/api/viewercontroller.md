# Viewer Controller
ViewerController is a class representing the 2D image rendering viewer of OsiriX.  It is used to obtain 
display information such as window settings and window title, and control contents (DCMPix and ROIs).

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 13-15)"}
----8<----
protos/types.proto:9:11
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc ViewerControllerXyz (ViewerControllerXyzRequest) returns (ViewerControllerXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.ViewerControllerXyz(request) # (1)
```

1. `response` is a  `ViewerControllerXyzResponse` class, and `request` a `ViewerControllerXyzRequest` class.

``` { .c++ title="osirix.proto (lines 99-125)"}
----8<----
protos/osirix.proto:99:125
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message ViewerControllerXyzResponse{
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

``` { .c++ title="viewercontroller.proto (lines 9-111)"}
----8<----
protos/viewercontroller.proto:9:91
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message ViewerControllerXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import viewercontroller_pb2

request = viewercontroller_pb2.ViewerControllerXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="viewercontroller.proto (lines 115-)"}
----8<----
protos/viewercontroller.proto:115:
----8<----
```