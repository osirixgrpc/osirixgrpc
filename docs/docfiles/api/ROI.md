# Regions of Interest
Below are the definitions for OsiriX ROI objects as extracted from the relevant protobuf files (including line-numbers).

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
is called in Python (for example) using the syntax
``` { .py}
ROIXyzResponse = osirix_stub.ROIXyz(ROIXyzRequest)
```

``` { .c++ title="osirix.proto (lines 27-44)"}
----8<----
protos/osirix.proto:27:44
----8<----
```

## Responses
``` { .c++ title="roi.proto (lines 9-59)"}
----8<----
protos/roi.proto:9:59
----8<----
```

## Requests
``` { .c++ title="roi.proto (lines 61-)"}
----8<----
protos/roi.proto:61:
----8<----
```