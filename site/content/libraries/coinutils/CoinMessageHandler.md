+++
title = "CoinMessageHandler"
description = "Base class for message handling."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMessageHandler.hpp"
api_url = "/api/coinutils/CoinMessageHandler.json"
+++

Base class for message handling.

<div class="api-link"><a href="/api/coinutils/CoinMessageHandler.json">JSON API</a></div>

## Description

The default behavior is described here: messages are printed, and (if the severity is sufficiently high) execution will be aborted. Inherit and redefine the methods print and checkSeverity to augment the behaviour.
Messages can be printed with or without a prefix; the prefix will consist of a source string, the external ID number, and a letter code, e.g., Clp6024W. A prefix makes the messages look less nimble but is very useful for "grep" etc.
Usage
The general approach to using the COIN messaging facility is as follows: Define your messages. For each message, you must supply an external ID number, a log (detail) level, and a format string. Typically, you define a convenience structure for this, something that's easy to use to create an array of initialised message definitions at compile time.
Create a CoinMessages object, sized to accommodate the number of messages you've defined. (Incremental growth will happen if necessary as messages are loaded, but it's inefficient.)
Load the messages into the CoinMessages object. Typically this entails creating a CoinOneMessage object for each message and passing it as a parameter to CoinMessages::addMessage(). You specify the message's internal ID as the other parameter to addMessage.
Create and use a CoinMessageHandler object to print messages.
See, for example, CoinMessage.hpp and CoinMessage.cpp for an example of the first three steps. Format codes below has a simple example of printing a message.
External ID numbers and severity
CoinMessageHandler assumes the following relationship between the external ID number of a message and the severity of the message: <3000 are informational ('I')
<6000 warnings ('W')
<9000 non-fatal errors ('E')
>=9000 aborts the program (after printing the message) ('S')
Log (detail) levels
The default behaviour is that a message will print if its detail level is less than or equal to the handler's log level. If all you want to do is set a single log level for the handler, use setLogLevel(int).
If you want to get fancy, here's how it really works: There's an array, logLevels_, which you can manipulate with setLogLevel(int,int). Each entry logLevels_[i] specifies the log level for messages of class i (see CoinMessages::class_). If logLevels_[0] is set to the magic number -1000 you get the simple behaviour described above, whatever the class of the messages. If logLevels_[0] is set to a valid log level (>= 0), then logLevels_[i] really is the log level for messages of class i.
Format codes
CoinMessageHandler can print integers (normal, long, and long long), doubles, characters, and strings. See the descriptions of the various << operators.
When processing a standard message with a format string, the formatting codes specified in the format string will be passed to the sprintf function, along with the argument. When generating a message with no format string, each << operator uses a simple format code appropriate for its argument. Consult the documentation for the standard printf facility for further information on format codes.
The special format code %? provides a hook to enable or disable printing. For each %? code, there must be a corresponding call to printing(bool). This provides a way to define optional parts in messages, delineated by the code %? in the format string. Printing can be suppressed for these optional parts, but any operands must still be supplied. For example, given the message string "A message with%? an optional integer %d and%? a double %g." installed in CoinMessages `exampleMsgs` with index 5, and `` `hdl`, the code hdl.message(5,exampleMsgs);
hdl.printing(true)<<42;
hdl.printing(true)<<53.5<<CoinMessageEol; will print A message with an optional integer 42 and a double 53.5. while hdl.message(5,exampleMsgs);
hdl.printing(false)<<42;
hdl.printing(true)<<53.5<<CoinMessageEol; will print A message with a double 53.5.
For additional examples of usage, see CoinMessageHandlerUnitTest in CoinMessageHandlerTest.cpp.

## Public Methods

### `print`

Print message, return 0 normally.

```cpp
int print()
```

### `checkSeverity`

Check message severity - if too bad then abort.

```cpp
void checkSeverity()
```

### `CoinMessageHandler`

Constructor.

```cpp
 CoinMessageHandler()
```

### `CoinMessageHandler`

Constructor to put to file pointer (won't be closed)

```cpp
 CoinMessageHandler(FILE * fp)
```

**Parameters:**

- `fp` (FILE *)

### `~CoinMessageHandler`

Destructor.

```cpp
 ~CoinMessageHandler()
```

### `CoinMessageHandler`

The copy constructor.

```cpp
 CoinMessageHandler(const CoinMessageHandler & )
```

**Parameters:**

- `` (const CoinMessageHandler &)

### `operator=`

Assignment operator.

```cpp
CoinMessageHandler & operator=(const CoinMessageHandler & )
```

**Parameters:**

- `` (const CoinMessageHandler &)

### `clone`

Clone.

```cpp
CoinMessageHandler * clone()
```

### `detail`

Get detail level of a message.

```cpp
int detail(int messageNumber, const CoinMessages & normalMessage)
```

**Parameters:**

- `messageNumber` (int)
- `normalMessage` (const CoinMessages &)

### `logLevel`

Get current log (detail) level.

```cpp
int logLevel()
```

### `setLogLevel`

Set current log (detail) level.

```cpp
void setLogLevel(int value)
```

**Parameters:**

- `value` (int)

### `logLevel`

Get alternative log level.

```cpp
int logLevel(int which)
```

**Parameters:**

- `which` (int)

### `setLogLevel`

Set alternative log level value.

```cpp
void setLogLevel(int which, int value)
```

**Parameters:**

- `which` (int)
- `value` (int)

### `setPrecision`

Set the number of significant digits for printing floating point numbers.

```cpp
void setPrecision(unsigned int new_precision)
```

**Parameters:**

- `new_precision` (unsigned int)

### `precision`

Current number of significant digits for printing floating point numbers.

```cpp
int precision()
```

### `setPrefix`

Switch message prefix on or off.

```cpp
void setPrefix(bool yesNo)
```

**Parameters:**

- `yesNo` (bool)

### `prefix`

Current setting for printing message prefix.

```cpp
bool prefix()
```

### `doubleValue`

Values of double fields already processed.

```cpp
double doubleValue(int position)
```

**Parameters:**

- `position` (int)

### `numberDoubleFields`

Number of double fields already processed.

```cpp
int numberDoubleFields()
```

### `intValue`

Values of integer fields already processed.

```cpp
CoinBigIndex intValue(int position)
```

**Parameters:**

- `position` (int)

### `numberIntFields`

Number of integer fields already processed.

```cpp
int numberIntFields()
```

### `charValue`

Values of char fields already processed.

```cpp
char charValue(int position)
```

**Parameters:**

- `position` (int)

### `numberCharFields`

Number of char fields already processed.

```cpp
int numberCharFields()
```

### `stringValue`

Values of string fields already processed.

```cpp
std::string stringValue(int position)
```

**Parameters:**

- `position` (int)

### `numberStringFields`

Number of string fields already processed.

```cpp
int numberStringFields()
```

### `currentMessage`

Current message.

```cpp
CoinOneMessage currentMessage()
```

### `currentSource`

Source of current message.

```cpp
std::string currentSource()
```

### `messageBuffer`

Output buffer.

```cpp
const char * messageBuffer()
```

### `highestNumber`

Highest message number (indicates any errors)

```cpp
int highestNumber()
```

### `filePointer`

Get current file pointer.

```cpp
FILE * filePointer()
```

### `setFilePointer`

Set new file pointer.

```cpp
void setFilePointer(FILE * fp)
```

**Parameters:**

- `fp` (FILE *)

### `message`

Start a message.

```cpp
CoinMessageHandler & message(int messageNumber, const CoinMessages & messages)
```

**Parameters:**

- `messageNumber` (int)
- `messages` (const CoinMessages &)

### `message`

Start or continue a message.

```cpp
CoinMessageHandler & message(int detail = -1)
```

**Parameters:**

- `detail` (int)

### `message`

Print a complete message.

```cpp
CoinMessageHandler & message(int externalNumber, const char * source, const char * msg, char severity, int detail = -1)
```

**Parameters:**

- `externalNumber` (int)
- `source` (const char *)
- `msg` (const char *)
- `severity` (char)
- `detail` (int)

### `operator<<`

Process an integer parameter value.

```cpp
CoinMessageHandler & operator<<(int intvalue)
```

**Parameters:**

- `intvalue` (int)

### `operator<<`

Process a long integer parameter value.

```cpp
CoinMessageHandler & operator<<(long longvalue)
```

**Parameters:**

- `longvalue` (long)

### `operator<<`

Process a long long integer parameter value.

```cpp
CoinMessageHandler & operator<<(long long longvalue)
```

**Parameters:**

- `longvalue` (long long)

### `operator<<`

Process a double parameter value.

```cpp
CoinMessageHandler & operator<<(double doublevalue)
```

**Parameters:**

- `doublevalue` (double)

### `operator<<`

Process a STL string parameter value.

```cpp
CoinMessageHandler & operator<<(const std::string & stringvalue)
```

**Parameters:**

- `stringvalue` (const std::string &)

### `operator<<`

Process a char parameter value.

```cpp
CoinMessageHandler & operator<<(char charvalue)
```

**Parameters:**

- `charvalue` (char)

### `operator<<`

Process a C-style string parameter value.

```cpp
CoinMessageHandler & operator<<(const char * stringvalue)
```

**Parameters:**

- `stringvalue` (const char *)

### `operator<<`

Process a marker.

```cpp
CoinMessageHandler & operator<<(CoinMessageMarker )
```

**Parameters:**

- `` (CoinMessageMarker)

### `finish`

Finish (and print) the message.

```cpp
int finish()
```

### `printing`

Enable or disable printing of an optional portion of a message.

```cpp
CoinMessageHandler & printing(bool onOff)
```

**Parameters:**

- `onOff` (bool)

## Source

Header: `layer-0/CoinUtils/src/CoinMessageHandler.hpp`
