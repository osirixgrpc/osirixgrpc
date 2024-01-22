# Getting Started

The following steps demonstrate how to install the plugin and subsequently start up a local OsiriX server and run 
scripts that can be defined in any source file on your system. To see how to write GRPC client code for use with 
OsiriXgrpc please see [defining client code](404.html).  

The OsiriXgrpc plugin consists of three core functionalities, all of which are accessible from the OsiriX submenus at
`Plugins` &rarr; `Database` &rarr; `osirixgrpc`:

1. __Server Configuration__ allows you to start and stop OsiriXgrpc servers. At lease one server must be active in 
   clients to be able to communicate with OsiriX.
2. __Script Management__ provides the list of client files currently registered by OsiriXgrpc, and includes information
   about where they are located and the location of executable to run the file. 
3. __Task Console__

## Installation
1. Download the [latest release](404.html).
2. Extract the downloaded archive.
3. Drag the `osirixgrpc.osirixplugin` file to the OsiriX application you want to install to.
4. Follow instructions for installation.

## Script Management 

> ___Note___: This is the long-winded way to do things. We _strongly_ recommend using the [pyosirix](404.html) library\
> for day-to-day development unless you want to do things the long way.

Whilst GRPC support many [languages](https://grpc.io/docs/languages/), including C++, Java, Go, Node.js, and PHP, we
currently only support use of Python. This is largely because the libraries available to Python for image processing
and machine-learning are generally state-of-the-art and come with a relatively short learning curve. If you are 
interested in generating the code for 
