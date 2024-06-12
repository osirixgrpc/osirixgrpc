# ROI Volumes
ROIVolume is a class representing volumetric regions of interest within an OsiriX 3D display window. It provides 
control of the visibility and color of the object.

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 25-27)"}
----8<----
protos/types.proto:25:27
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc ROIVolumeXyz (ROIVolumeXyzRequest) returns (ROIVolumeXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.ROIVolumeXyz(request) # (1)
```

1. `response` is a  `ROIVolumeXyzResponse` class, and `request` a `ROIVolumeXyzRequest` class.

``` { .c++ title="osirix.proto (lines 53-63)"}
----8<----
protos/osirix.proto:53:63
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message ROIVolumeXyzResponse{
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

``` { .c++ title="roivolume.proto (lines 9-44)"}
----8<----
protos/roivolume.proto:9:44
----8<----
```

## Requests
By convention, any request defined with syntax
``` { .c++}
message ROIVolumeXyzRequest{
    type_1 arg_1 = 1;
    type_2 arg_2 = 2; // (1)
    ...
}
```

1. The numbers on the RHS should be ignored.  They are necessary only for protobuf file definitions.

is created in Python (for example) using syntax
``` { .py}
from osirixgrpc import roivolume_pb2

request = roivolume_pb2.ROIVolumeXyzRequest(arg1 = x1, arg2 = x2, ...)
```

``` { .c++ title="roivolume.proto (lines 48-)"}
----8<----
protos/roivolume.proto:48:
----8<----
```