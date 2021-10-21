This directory is used to generate plantuml diagrams of the workflow of osirixgrpc. Currently this consists of a simple class diagram to provide the overall architecture.  The source code is currently implemented in a single file called "grpcosirix_structure.txt", which can be compiled into a svg file using the command:

```
java -jar path/to/planumml.jar -verbose -teps path/to/grpcosirix_structure.txt
```

This will require download of the plantumml.jar file from the plantuml website (https://plantuml.com/download).  In addition to this, the system will require Graphviz (https://plantuml.com/graphviz-dot).

Currently platnuml does not support pdf generation so use an existing package (like Inkscape) to do this.
