# SLog Usage Examples
This directory contains simple examples demonstrating the usage of SLog.

## How to Run:
To compile and run an example, use the following commands:

```sh
$ gcc <example-name.c> -o <example-name> -lslog
$ ./<example-name> <args>
```

### Demo
To run the demo:

```sh
$ gcc demo.c -o demo -lslog
$ ./demo demo.log
```

### Basic Example
To run the basic example:

```sh
$ gcc basic-usage.c -o basic-usage -lslog
$ ./basic-usage
```

### File Logging Example
To run the file logging example:

```sh
$ gcc file-logging.c -o file-logging -lslog
$ ./file-logging
```

### Multi-threaded Example (*Nix only)
To run the multi-threaded example:

```sh
$ gcc multi-thread.c -o multi-thread -lslog -lpthread
$ ./multi-thread
```

## Notes
If you have not installed the SLog library, specify the path to the library
using the -L option:

```sh
$ gcc <example-name.c> -o <example-name> -L/path/to/libslog.a -lslog
```
