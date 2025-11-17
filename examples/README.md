# SLog Usage Examples
This directory contains simple examples demonstrating the usage of SLog.

## How to Run:
To compile and run an example, use the following commands:

```sh
$ gcc <example_name.c> -o <example_name> -lslog
$ ./<example_name> <args>
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
$ gcc basic_example.c -o basic_example -lslog
$ ./basic_example basic_log.log
```

### File Logging Example
To run the file logging example:

```sh
$ gcc file_logging_example.c -o file_logging_example -lslog
$ ./file_logging_example file_log.log
```

### Multi-threaded Example (*Nix only)
To run the multi-threaded example:

```sh
$ gcc multi_threaded_example.c -o multi_threaded_example -lslog -lpthread
$ ./multi_threaded_example mt_log.log
```

## Notes
If you have not installed the SLog library, specify the path to the library
using the -L option:

```sh
$ gcc <example_name.c> -o <example_name> -L/path/to/libslog.a -lslog
```
