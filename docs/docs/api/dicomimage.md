# Dicom Image
DicomImage is a class representing a dicom file/slice within the OsiriX database. It contains information including 
patient details, modality, and file location. 

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 29-31)"}
----8<----
protos/types.proto:29:31
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc DicomImageXyz (DicomImage) returns (DicomImageXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.DicomImageXyz(request) # (1)
```

1. `response` is a  `DicomImageXyzResponse` class, and `request` a `DicomImage` class.

``` { .c++ title="osirix.proto (lines 134-143)"}
----8<----
protos/osirix.proto:134:143
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message DicomImageXyzResponse{
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

``` { .c++ title="dicomimage.proto (lines 9-)"}
----8<----
protos/dicomimage.proto:9:
----8<----
```

## Requests
No specialized requests available for this class (class is immutable).
