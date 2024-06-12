# Regions of Interest
ROI is a class representing regions of interest within an OsiriX 2D display window. It provides control of the 
vertices/mask, color, and thickness of the object.

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 21-23)"}
----8<----
protos/types.proto:21:23
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc ROIXyz (ROIXyzRequest) returns (ROIXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.ROIXyz(request) # (1)
```

1. `response` is a  `ROIXyzResponse` class, and `request` a `ROIXyzRequest` class.

``` { .c++ title="osirix.proto (lines 32-50)"}
----8<----
protos/osirix.proto:32:50
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message ROIXyzResponse{
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

``` { .c++ title="roi.proto (lines 9-59)"}
----8<----
protos/roi.proto:9:59
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message ROIXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import roi_pb2

request = roi_pb2.ROIXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="roi.proto (lines 62-)"}
----8<----
protos/roi.proto:62:
----8<----
```