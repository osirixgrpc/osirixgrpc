# Dicom Series
DicomSeries is a class representing a group of DicomImage objects within the same series. It contains information 
including patient details, modality, and file location(s). 

## Type
All types only contain a single parameter, the UUID of the underlying OsiriX object.
``` { .c++ title="types.proto (lines 33-35)"}
----8<----
protos/types.proto:33:35
----8<----
```

## Methods
By convention, any method defined with syntax 
``` { .c++}
rpc DicomSeriesXyz (DicomSeries) returns (DicomSeriesXyzResponse) {}
```
is called in Python (for example) using syntax
``` { .py}
response = osirix_stub.DicomSeriesXyz(request) # (1)
```

1. `response` is a  `DicomSeriesXyzResponse` class, and `request` a `DicomSeries` class.

``` { .c++ title="osirix.proto (lines 146-158)"}
----8<----
protos/osirix.proto:146:158
----8<----
```

## Responses
By convention, any response defined with syntax
``` { .c++}
message DicomSeriesXyzResponse{
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

``` { .c++ title="dicomseries.proto (lines 9-)"}
----8<----
protos/dicomseries.proto:9:
----8<----
```

## Requests
No specialized requests available for this class (class is immutable).
