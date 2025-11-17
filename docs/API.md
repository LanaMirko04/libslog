# API Reference

## Header files

- [include/slog.h](#file-includeslogh)

## File include/slog.h

_SLog (Sh\*tty Logging) library._

**Date:**

2023-05-30 



**Author:**

Mirko Lana [[lana.mirko@icloud.com](mailto:lana.mirko@icloud.com)]

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**SlogConfig**](#struct-slogconfig) <br>_Configuration structure for initializing the SLog system._ |
| enum  | [**SlogLevel**](#enum-sloglevel)  <br>_Enumeration representing different log levels._ |
| enum  | [**SlogReturnCode**](#enum-slogreturncode)  <br>_Enumeration containing all possible return codes._ |
| struct | [**Slogger**](#struct-slogger) <br>_The SLog logger structure._ |

## Functions

| Type | Name |
| ---: | :--- |
|  enum [**SlogReturnCode**](#enum-slogreturncode) | [**int\_slog\_default\_flush**](#function-int_slog_default_flush) (const void \*ctx) <br>_Default (dummy) flush function._ |
|  enum [**SlogReturnCode**](#enum-slogreturncode) | [**int\_slog\_default\_write**](#function-int_slog_default_write) (const void \*ctx, const char \*fmt, ...) <br>_Default write function._ |
|  enum [**SlogReturnCode**](#enum-slogreturncode) | [**int\_slog\_emit**](#function-int_slog_emit) (const struct [**Slogger**](#struct-slogger) \*logger, enum [**SlogLevel**](#enum-sloglevel) level, const char \*fmt, ...) <br>_Emit a log message using the default logger._ |
|  const struct [**Slogger**](#struct-slogger) \* | [**slog\_get\_default\_logger**](#function-slog_get_default_logger) (void) <br>_Get the current default logger for the logging system._ |
|  enum [**SlogLevel**](#enum-sloglevel) | [**slog\_get\_emit\_level**](#function-slog_get_emit_level) (void) <br>_Get the current log emit level._ |
|  void | [**slog\_init**](#function-slog_init) (const struct [**SlogConfig**](#struct-slogconfig) \*cfg) <br>_Initialize the SLog logging system._ |
|  const char \* | [**slog\_level\_to\_str**](#function-slog_level_to_str) (enum [**SlogLevel**](#enum-sloglevel) level) <br>_Convert_ [_**SlogLevel**_](#enum-sloglevel)_ enum to string representation._ |
|  enum [**SlogReturnCode**](#enum-slogreturncode) | [**slog\_set\_default\_logger**](#function-slog_set_default_logger) (const struct [**Slogger**](#struct-slogger) \*logger, struct [**Slogger**](#struct-slogger) \*old\_logger) <br>_Set the default logger for the logging system._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SLOG\_ANSI\_BOLD**](#define-slog_ansi_bold)  "\033[1m"<br> |
| define  | [**SLOG\_ANSI\_CYAN**](#define-slog_ansi_cyan)  "\033[0;36m"<br> |
| define  | [**SLOG\_ANSI\_GRAY**](#define-slog_ansi_gray)  "\033[0;37m"<br> |
| define  | [**SLOG\_ANSI\_GREEN**](#define-slog_ansi_green)  "\033[0;32m"<br> |
| define  | [**SLOG\_ANSI\_RED**](#define-slog_ansi_red)  "\033[0;31m"<br> |
| define  | [**SLOG\_ANSI\_RESET**](#define-slog_ansi_reset)  "\033[0m"<br> |
| define  | [**SLOG\_ANSI\_YELLOW**](#define-slog_ansi_yellow)  "\033[0;33m"<br> |
| define  | [**SLOG\_DEBUG**](#define-slog_debug) (fmt, ...) [**SLOG\_EMIT**](#define-slog_emit)([**slog\_get\_default\_logger**](#function-slog_get_default_logger)(),SLOG\_LEVEL\_DEBUG, fmt, ##\_\_VA\_ARGS\_\_)<br>_Emit a debug log message._ |
| define  | [**SLOG\_EMIT**](#define-slog_emit) (logger, lv, fmt, ...) [**int\_slog\_emit**](#function-int_slog_emit)((logger), (lv), " %s:%d -&gt; " fmt "\n", \_\_FILE\_\_, \_\_LINE\_\_, ##\_\_VA\_ARGS\_\_)<br>_Emit a log message using the specified logger._ |
| define  | [**SLOG\_EMIT\_BUFFER\_SIZE**](#define-slog_emit_buffer_size)  1024<br>_Size of the internal buffer used for log message formatting._ |
| define  | [**SLOG\_ERROR**](#define-slog_error) (fmt, ...) [**SLOG\_EMIT**](#define-slog_emit)([**slog\_get\_default\_logger**](#function-slog_get_default_logger)(),SLOG\_LEVEL\_ERROR, fmt, ##\_\_VA\_ARGS\_\_)<br>_Emit an error log message._ |
| define  | [**SLOG\_INFO**](#define-slog_info) (fmt, ...) [**SLOG\_EMIT**](#define-slog_emit)([**slog\_get\_default\_logger**](#function-slog_get_default_logger)(),SLOG\_LEVEL\_INFO, fmt, ##\_\_VA\_ARGS\_\_)<br>_Emit an informational log message._ |
| define  | [**SLOG\_INIT\_DEFAULT\_LOGGER**](#define-slog_init_default_logger)  <br> |
| define  | [**SLOG\_WARN**](#define-slog_warn) (fmt, ...) [**SLOG\_EMIT**](#define-slog_emit)([**slog\_get\_default\_logger**](#function-slog_get_default_logger)(),SLOG\_LEVEL\_WARN, fmt, ##\_\_VA\_ARGS\_\_)<br>_Emit a warning log message._ |

## Structures and Types Documentation

### struct `SlogConfig`

_Configuration structure for initializing the SLog system._

Variables:

-  struct [**Slogger**](#struct-slogger) default_logger  <br>Default logger configuration.

-  void(\* enter_cs  <br>Function pointer to enter critical section.

-  void(\* exit_cs  <br>Function pointer to exit critical section.

### enum `SlogLevel`

_Enumeration representing different log levels._
```c
enum SlogLevel {
    SLOG_LEVEL_NONE = 0x00,
    SLOG_LEVEL_INFO = 0x01,
    SLOG_LEVEL_ERROR = 0x02,
    SLOG_LEVEL_WARN = 0x04,
    SLOG_LEVEL_DEBUG = 0x08,
    SLOG_LEVEL_ALL = 0x0F
};
```

### enum `SlogReturnCode`

_Enumeration containing all possible return codes._
```c
enum SlogReturnCode {
    SLOG_RC_FAIL = -1,
    SLOG_RC_OK,
    SLOG_RC_INVALID_ARG,
    SLOG_RC_IO_ERR
};
```

### struct `Slogger`

_The SLog logger structure._

Variables:

-  bool apply_colors  <br>Flag to apply colors to the log messages.

-  void \* ctx  <br>User-defined context pointer.

-  enum [**SlogReturnCode**](#enum-slogreturncode)(\* flush_fn  <br>Flush function pointer.

-  uint8\_t lv  <br>Log level for this logger.

-  enum [**SlogReturnCode**](#enum-slogreturncode)(\* write_fn  <br>Write function pointer.


## Functions Documentation

### function `int_slog_default_flush`

_Default (dummy) flush function._
```c
enum SlogReturnCode int_slog_default_flush (
    const void *ctx
) 
```


**Parameters:**


* `ctx` User-defined context pointer. 


**Returns:**

SLOG\_RC\_OK every time.
### function `int_slog_default_write`

_Default write function._
```c
enum SlogReturnCode int_slog_default_write (
    const void *ctx,
    const char *fmt,
    ...
) 
```


**Parameters:**


* `ctx` User-defined context pointer. 
* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### function `int_slog_emit`

_Emit a log message using the default logger._
```c
enum SlogReturnCode int_slog_emit (
    const struct Slogger *logger,
    enum SlogLevel level,
    const char *fmt,
    ...
) 
```


**Parameters:**


* `level` Log level of the message. 
* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### function `slog_get_default_logger`

_Get the current default logger for the logging system._
```c
const struct Slogger * slog_get_default_logger (
    void
) 
```


**Returns:**

Pointer to the current default [**Slogger**](#struct-slogger).
### function `slog_get_emit_level`

_Get the current log emit level._
```c
enum SlogLevel slog_get_emit_level (
    void
) 
```


**Returns:**

Current log emit level as an enum [**SlogLevel**](#enum-sloglevel).



**Note:**

This level is the last level set by the SLOG\_EMIT macro.
### function `slog_init`

_Initialize the SLog logging system._
```c
void slog_init (
    const struct SlogConfig *cfg
) 
```


**Parameters:**


* `cfg` Pointer to the [**SlogConfig**](#struct-slogconfig) structure.
### function `slog_level_to_str`

_Convert_ [_**SlogLevel**_](#enum-sloglevel)_ enum to string representation._
```c
const char * slog_level_to_str (
    enum SlogLevel level
) 
```


SLOG\_DISABLE\_LOGGING\_SYSTEM
### function `slog_set_default_logger`

_Set the default logger for the logging system._
```c
enum SlogReturnCode slog_set_default_logger (
    const struct Slogger *logger,
    struct Slogger *old_logger
) 
```


**Parameters:**


* `logger` Pointer to the [**Slogger**](#struct-slogger) to set as default.
* `old_logger` Pointer to store the previous default logger (can be NULL). 


**Returns:**

SLOG\_RC\_OK on success, or an error code on failure.

## Macros Documentation

### define `SLOG_ANSI_BOLD`

```c
#define SLOG_ANSI_BOLD "\033[1m"
```


ANSI escape code for bold text.
### define `SLOG_ANSI_CYAN`

```c
#define SLOG_ANSI_CYAN "\033[0;36m"
```


ANSI escape code for cyan foreground color.
### define `SLOG_ANSI_GRAY`

```c
#define SLOG_ANSI_GRAY "\033[0;37m"
```


ANSI escape code for gray foreground color.
### define `SLOG_ANSI_GREEN`

```c
#define SLOG_ANSI_GREEN "\033[0;32m"
```


ANSI escape code for green foreground color.
### define `SLOG_ANSI_RED`

```c
#define SLOG_ANSI_RED "\033[0;31m"
```


ANSI escape code for red foreground color.
### define `SLOG_ANSI_RESET`

```c
#define SLOG_ANSI_RESET "\033[0m"
```


ANSI escape code for reset.
### define `SLOG_ANSI_YELLOW`

```c
#define SLOG_ANSI_YELLOW "\033[0;33m"
```


ANSI escape code for yellow foreground color.
### define `SLOG_DEBUG`

_Emit a debug log message._
```c
#define SLOG_DEBUG (
    fmt,
    ...
) SLOG_EMIT ( slog_get_default_logger (), SLOG_LEVEL_DEBUG , fmt, ##__VA_ARGS__)
```


**Parameters:**


* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### define `SLOG_EMIT`

_Emit a log message using the specified logger._
```c
#define SLOG_EMIT (
    logger,
    lv,
    fmt,
    ...
) int_slog_emit ((logger), (lv), " %s:%d -> " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
```


\_\_cplusplus



**Parameters:**


* `logger` Pointer to the [**Slogger**](#struct-slogger) to use.
* `lv` Log level of the message. 
* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### define `SLOG_EMIT_BUFFER_SIZE`

_Size of the internal buffer used for log message formatting._
```c
#define SLOG_EMIT_BUFFER_SIZE 1024
```


**Note:**

This value can be overridden by defining SLOG\_EMIT\_BUFFER\_SIZE before including this header file or during compilation (-d flag).
### define `SLOG_ERROR`

_Emit an error log message._
```c
#define SLOG_ERROR (
    fmt,
    ...
) SLOG_EMIT ( slog_get_default_logger (), SLOG_LEVEL_ERROR , fmt, ##__VA_ARGS__)
```


**Parameters:**


* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### define `SLOG_INFO`

_Emit an informational log message._
```c
#define SLOG_INFO (
    fmt,
    ...
) SLOG_EMIT ( slog_get_default_logger (), SLOG_LEVEL_INFO , fmt, ##__VA_ARGS__)
```


**Parameters:**


* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.
### define `SLOG_INIT_DEFAULT_LOGGER`

```c
#define SLOG_INIT_DEFAULT_LOGGER {         \
    .write_fn = int_slog_default_write ,    \
    .flush_fn = int_slog_default_flush ,    \
    .ctx = NULL,                           \
    .lv = SLOG_LEVEL_ALL ,                  \
    .apply_colors = isatty(fileno(stdout)) \
}
```


SLOG\_EMIT\_BUFFER\_SIZE Default [**Slogger**](#struct-slogger) initializer.
### define `SLOG_WARN`

_Emit a warning log message._
```c
#define SLOG_WARN (
    fmt,
    ...
) SLOG_EMIT ( slog_get_default_logger (), SLOG_LEVEL_WARN , fmt, ##__VA_ARGS__)
```


**Parameters:**


* `fmt` Format string. 
* `...` Variable arguments. 


**Returns:**

SLOG\_RC\_OK on success, otherwise an error code.

