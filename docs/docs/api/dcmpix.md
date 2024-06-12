# DCMPix
DCMPix is a class of objects contained within a 2D OsiriX viewer. It contains information about the displayed
image, including the number fo rows/columns, the source file from which it is generated, whether it is greyscale
of ARGB format, and ultimately the pixel data.

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 17-19)"}
----8<----
protos/types.proto:17:19
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc DCMPixXyz (DCMPixXyzRequest) returns (DCMPixXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.DCMPixXyz(request) # (1)
```

1. `response` is a  `DCMPixXyzResponse` class, and `request` a `DCMPixXyzRequest` class.

``` { .c++ title="osirix.proto (lines 66-82)"}
----8<----
protos/osirix.proto:66:82
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message DCMPixXyzResponse{
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

``` { .c++ title="dcmpix.proto (lines 9-95)"}
----8<----
protos/dcmpix.proto:9:95
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message DCMPixXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import dcmpix_pb2

request = dcmpix_pb2.DCMPixXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="dcmpix.proto (lines 98-)"}
----8<----
protos/dcmpix.proto:98:
----8<----
```