# Dicom Study
DicomStudy is a class representing a group of DicomSeries objects within the same study. It contains information 
including patient details, modality, and file location(s). 

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 37-39)"}
----8<----
protos/types.proto:37:39
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc DicomStudyXyz (DicomStudy) returns (DicomStudyXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.DicomStudyXyz(request) # (1)
```

1. `response` is a  `DicomStudyXyzResponse` class, and `request` a `DicomStudy` class.

``` { .c++ title="osirix.proto (lines 161-180)"}
----8<----
protos/osirix.proto:161:180
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message DicomStudyXyzResponse{
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

``` { .c++ title="dicomstudy.proto (lines 9-)"}
----8<----
protos/dicomstudy.proto:9:
----8<----
```

## Requests
No specialized requests available for this class (class is immutable).
