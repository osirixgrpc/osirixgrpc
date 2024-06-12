# VR Controller
VRController is a class representing the 3D volume rendering viewer of OsiriX.  It is used to obtain/control 
display information such as window settings, window title, and the type of volume render.

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 13-15)"}
----8<----
protos/types.proto:13:15
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc VRControllerXyz (VRControllerXyzRequest) returns (VRControllerXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.VRControllerXyz(request) # (1)
```

1. `response` is a  `VRControllerXyzResponse` class, and `request` a `VRControllerXyzRequest` class.

``` { .c++ title="osirix.proto (lines 85-96)"}
----8<----
protos/osirix.proto:85:96
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message VRControllerXyzResponse{
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

``` { .c++ title="vrcontroller.proto (lines 9-43)"}
----8<----
protos/vrcontroller.proto:9:43
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message VRControllerXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import vrcontroller_pb2

request = vrcontroller_pb2.VRControllerXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="vrcontroller.proto (lines 46-)"}
----8<----
protos/vrcontroller.proto:46:
----8<----
```