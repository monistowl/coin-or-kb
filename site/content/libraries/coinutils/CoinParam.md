+++
title = "CoinParam"
description = "A base class for keyword value command line parameters."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinParam.hpp"
api_url = "/api/coinutils/CoinParam.json"
+++

A base class for keyword value command line parameters.


## Description

The underlying paradigm is that a parameter specifies an action to be performed on a target object. The base class provides two function pointers, a push function and a pull function. By convention, a push function will set some value in the target object or perform some action using the target object. A pull function will retrieve some value from the target object. This is only a convention, however; CoinParam and associated utilities make no use of these functions and have no hardcoded notion of how they should be used.
The action to be performed, and the target object, will be specific to a particular application. It is expected that users will derive application-specific parameter classes from this base class. A derived class will typically add fields and methods to set/get a code for the action to be performed (often, an enum class) and the target object (often, a pointer or reference).
Facilities provided by the base class and associated utility routines include: Support for common parameter types with numeric, string, or keyword values.
Support for short and long help messages.
Pointers to push and pull functions as described above.
Command line parsing and keyword matching.
All utility routines are declared in the CoinParamUtils namespace.
The base class recognises five types of parameters: actions (which require no value); numeric parameters with integer or real (double) values; keyword parameters, where the value is one of a defined set of value-keywords; and string parameters (where the value is a string). The base class supports the definition of a valid range, a default value, and short and long help messages for a parameter.
As defined by the CoinParamFunc typedef, push and pull functions should take a single parameter, a pointer to a CoinParam. Typically this object will actually be a derived class as described above, and the implementation function will have access to all capabilities of CoinParam and of the derived class.
When specified as command line parameters, the expected syntax is -keyword value or -keyword=value. You can also use the Gnu double-dash style, --keyword. Spaces around the = will not work.
The keyword (name) for a parameter can be defined with an ! to mark the minimal match point. For example, allow!ableGap will be considered matched by the strings allow, allowa, allowab, etc. Similarly, the value-keyword strings for keyword parameters can be defined with ! to mark the minimal match point. Matching of keywords and value-keywords is not case sensitive.

## Public Methods

### `CoinParam`

Default constructor.

```cpp
 CoinParam()
```

### `CoinParam`

Constructor for a parameter with a double value.

```cpp
 CoinParam(std::string name, std::string help, double lower = -, double upper, std::string longHelp = "", CoinDisplayPriority displayPriority)
```

**Parameters:**

- `name` (std::string)
- `help` (std::string)
- `lower` (double)
- `upper` (double)
- `longHelp` (std::string)
- `displayPriority` (CoinDisplayPriority)

### `CoinParam`

Constructor for a parameter with an integer value.

```cpp
 CoinParam(std::string name, std::string help, int lower = -, int upper, std::string longHelp = "", CoinDisplayPriority displayPriority)
```

**Parameters:**

- `name` (std::string)
- `help` (std::string)
- `lower` (int)
- `upper` (int)
- `longHelp` (std::string)
- `displayPriority` (CoinDisplayPriority)

### `CoinParam`

Constructor for any parameter taking a string (or no) value (all others). Type is not optional to resolve ambiguity.

```cpp
 CoinParam(std::string name, CoinParamType type, std::string help, std::string longHelp = "", CoinDisplayPriority displayPriority)
```

**Parameters:**

- `name` (std::string)
- `type` (CoinParamType)
- `help` (std::string)
- `longHelp` (std::string)
- `displayPriority` (CoinDisplayPriority)

### `CoinParam`

Copy constructor.

```cpp
 CoinParam(const CoinParam & orig)
```

**Parameters:**

- `orig` (const CoinParam &)

### `clone`

Clone.

```cpp
CoinParam * clone()
```

### `operator=`

Assignment.

```cpp
CoinParam & operator=(const CoinParam & rhs)
```

**Parameters:**

- `rhs` (const CoinParam &)

### `~CoinParam`

Destructor.

```cpp
 ~CoinParam()
```

### `setup`

These mirror the constructors with the addition of long help.

```cpp
void setup(std::string name, std::string help, double lower = -, double upper, std::string longHelp = "", CoinDisplayPriority display)
```

**Parameters:**

- `name` (std::string)
- `help` (std::string)
- `lower` (double)
- `upper` (double)
- `longHelp` (std::string)
- `display` (CoinDisplayPriority)

### `setup`

```cpp
void setup(std::string name, std::string help, int lower = -, int upper, std::string longHelp = "", CoinDisplayPriority display)
```

**Parameters:**

- `name` (std::string)
- `help` (std::string)
- `lower` (int)
- `upper` (int)
- `longHelp` (std::string)
- `display` (CoinDisplayPriority)

### `setup`

```cpp
void setup(std::string name, std::string help, std::string longHelp = "", CoinDisplayPriority display)
```

**Parameters:**

- `name` (std::string)
- `help` (std::string)
- `longHelp` (std::string)
- `display` (CoinDisplayPriority)

### `setVal`

```cpp
int setVal(std::string value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setVal`

```cpp
int setVal(double value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (double)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setVal`

```cpp
int setVal(int value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setDefault`

```cpp
int setDefault(std::string value, std::string * message = NULL)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)

### `setDefault`

```cpp
int setDefault(double value, std::string * message = NULL)
```

**Parameters:**

- `value` (double)
- `message` (std::string *)

### `setDefault`

```cpp
int setDefault(int value, std::string * message = NULL)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)

### `restoreDefault`

```cpp
int restoreDefault()
```

### `getVal`

```cpp
int getVal(std::string & value)
```

**Parameters:**

- `value` (std::string &)

### `getVal`

```cpp
int getVal(double & value)
```

**Parameters:**

- `value` (double &)

### `getVal`

```cpp
int getVal(int & value)
```

**Parameters:**

- `value` (int &)

### `readValue`

```cpp
int readValue(std::deque< std::string > & inputQueue, std::string & value, std::string * message = NULL)
```

**Parameters:**

- `inputQueue` (std::deque< std::string > &)
- `value` (std::string &)
- `message` (std::string *)

### `readValue`

```cpp
int readValue(std::deque< std::string > & inputQueue, int & value, std::string * message = NULL)
```

**Parameters:**

- `inputQueue` (std::deque< std::string > &)
- `value` (int &)
- `message` (std::string *)

### `readValue`

```cpp
int readValue(std::deque< std::string > & inputQueue, double & value, std::string * message = NULL)
```

**Parameters:**

- `inputQueue` (std::deque< std::string > &)
- `value` (double &)
- `message` (std::string *)

### `appendKwd`

Add an additional value-keyword to a keyword parameter.

```cpp
void appendKwd(std::string kwd, int index)
```

**Parameters:**

- `kwd` (std::string)
- `index` (int)

### `appendKwd`

Add an additional value-keyword to a keyword parameter, generating sequential mode values.

```cpp
void appendKwd(std::string kwd)
```

**Parameters:**

- `kwd` (std::string)

### `kwdToMode`

Return the integer associated with the specified value-keyword.

```cpp
int kwdToMode(std::string kwd)
```

**Parameters:**

- `kwd` (std::string)

### `kwdVal`

Return the value-keyword that is the current value of the keyword parameter.

```cpp
std::string kwdVal()
```

### `modeVal`

Return the integer mode value of the current keyword parameter.

```cpp
int modeVal()
```

### `modeString`

Return the string for an integer mode of keyword parameter.

```cpp
std::string modeString(int value)
```

**Parameters:**

- `value` (int)

### `setModeVal`

Set the value of the keyword parameter using the integer associated with a value-keyword.

```cpp
int setModeVal(int value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setModeValDefault`

Set the default value of the keyword parameter using the integer associated with a value-keyword.

```cpp
int setModeValDefault(int value, std::string * message = NULL)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)

### `setKwdVal`

Set the value of the keyword parameter using a value-keyword string.

```cpp
int setKwdVal(const std::string value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (const std::string)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setKwdValDefault`

Set the default value of the keyword parameter using a value-keyword string.

```cpp
int setKwdValDefault(const std::string value, std::string * message = NULL)
```

**Parameters:**

- `value` (const std::string)
- `message` (std::string *)

### `printKwds`

Prints the set of value-keywords defined for this keyword parameter.

```cpp
std::string printKwds()
```

### `definedKwds`

Set of valid value-keywords for a keyword parameter.

```cpp
const std::map< std::string, int > & definedKwds()
```

### `definedKwdsSorted`

Valid value-keywords for a keyword parameter sorted by integer mode.

```cpp
std::vector< std::string > definedKwdsSorted()
```

### `setStrVal`

Set the value of a string parameter.

```cpp
int setStrVal(std::string value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setStrValDefault`

Set the default value of a string parameter.

```cpp
int setStrValDefault(std::string value, std::string * message = NULL)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)

### `strVal`

Get the value of a string parameter.

```cpp
std::string strVal()
```

### `setDirName`

Set the value of a directory parameter.

```cpp
int setDirName(std::string value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setDirNameDefault`

Set the default value of a directory parameter.

```cpp
int setDirNameDefault(std::string value, std::string * message = NULL)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)

### `dirName`

Get the value of a directory parameter.

```cpp
std::string dirName()
```

### `setFileName`

Set the value of a file name parameter.

```cpp
int setFileName(std::string value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setFileNameDefault`

Set the default value of a file name parameter.

```cpp
int setFileNameDefault(std::string value, std::string * message = NULL)
```

**Parameters:**

- `value` (std::string)
- `message` (std::string *)

### `fileName`

Get the value of a file name parameter.

```cpp
std::string fileName()
```

### `setDblVal`

Set the value of a double parameter.

```cpp
int setDblVal(double value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (double)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setDblValDefault`

Set the default value of a double parameter.

```cpp
int setDblValDefault(double value, std::string * message = NULL)
```

**Parameters:**

- `value` (double)
- `message` (std::string *)

### `dblVal`

Get the value of a double parameter.

```cpp
double dblVal()
```

### `setLowerDblVal`

Set the lower value of an double parameter.

```cpp
void setLowerDblVal(double value)
```

**Parameters:**

- `value` (double)

### `lowerDblVal`

Get the lower value of a double parameter.

```cpp
double lowerDblVal()
```

### `setUpperDblVal`

Set the upper value of a double parameter.

```cpp
void setUpperDblVal(double value)
```

**Parameters:**

- `value` (double)

### `upperDblVal`

Get the upper value of a double parameter.

```cpp
double upperDblVal()
```

### `setIntVal`

Set the value of a integer parameter.

```cpp
int setIntVal(int value, std::string * message = NULL, ParamPushMode pMode)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)
- `pMode` (ParamPushMode)

### `setIntValDefault`

Set the value of a integer parameter.

```cpp
int setIntValDefault(int value, std::string * message = NULL)
```

**Parameters:**

- `value` (int)
- `message` (std::string *)

### `intVal`

Get the value of a integer parameter.

```cpp
int intVal()
```

### `setLowerIntVal`

Set the lower value of an integer parameter.

```cpp
void setLowerIntVal(int value)
```

**Parameters:**

- `value` (int)

### `lowerIntVal`

Get the lower value of a integer parameter.

```cpp
int lowerIntVal()
```

### `setUpperIntVal`

Set the upper value of a integer parameter.

```cpp
void setUpperIntVal(int value)
```

**Parameters:**

- `value` (int)

### `upperIntVal`

Get the upper value of a integer parameter.

```cpp
int upperIntVal()
```

### `printOptions`

Print possible options for a keyword parameter.

```cpp
void printOptions(std::string * message = NULL)
```

**Parameters:**

- `message` (std::string *)

### `setShortHelp`

Add a short help string to a parameter.

```cpp
void setShortHelp(const std::string help)
```

**Parameters:**

- `help` (const std::string)

### `shortHelp`

Retrieve the short help string.

```cpp
std::string shortHelp()
```

### `setLongHelp`

Add a long help message to a parameter.

```cpp
void setLongHelp(const std::string help)
```

**Parameters:**

- `help` (const std::string)

### `longHelp`

Retrieve the long help message.

```cpp
std::string longHelp()
```

### `printLongHelp`

Print long help.

```cpp
std::string printLongHelp()
```

### `type`

Return the type of the parameter.

```cpp
CoinParamType type()
```

### `setType`

Set the type of the parameter.

```cpp
void setType(CoinParamType type)
```

**Parameters:**

- `type` (CoinParamType)

### `name`

Return the parameter keyword (name) string.

```cpp
std::string name()
```

### `setName`

Set the parameter keyword (name) string.

```cpp
void setName(std::string name)
```

**Parameters:**

- `name` (std::string)

### `matches`

Check if the specified string matches the parameter keyword (name) string.

```cpp
int matches(std::string input)
```

**Parameters:**

- `input` (std::string)

### `matchName`

Return the parameter keyword (name) string formatted to show the minimum match length.

```cpp
std::string matchName()
```

### `lengthMatchName`

Return the length of the formatted paramter name for printing.

```cpp
int lengthMatchName()
```

### `setDisplayPriority`

Set visibility of parameter.

```cpp
void setDisplayPriority(CoinDisplayPriority display)
```

**Parameters:**

- `display` (CoinDisplayPriority)

### `getDisplayPriority`

Get visibility of parameter.

```cpp
CoinDisplayPriority getDisplayPriority()
```

### `pushFunc`

Get push function.

```cpp
CoinParamFunc pushFunc()
```

### `setPushFunc`

Set push function.

```cpp
void setPushFunc(CoinParamFunc func)
```

**Parameters:**

- `func` (CoinParamFunc)

### `pullFunc`

Get pull function.

```cpp
CoinParamFunc pullFunc()
```

### `setPullFunc`

Set pull function.

```cpp
void setPullFunc(CoinParamFunc func)
```

**Parameters:**

- `func` (CoinParamFunc)

### `operator<<`

A stream output function for a CoinParam object.

```cpp
COINUTILSLIB_EXPORT std::ostream & operator<<(std::ostream & s, const CoinParam & param)
```

**Parameters:**

- `s` (std::ostream &)
- `param` (const CoinParam &)

### `matchParam`

Scan a parameter vector for parameters whose keyword (name) string matches `name` using minimal match rules.

```cpp
COINUTILSLIB_EXPORT int matchParam(const CoinParamVec & paramVec, std::string name, int & matchNdx, int & shortCnt)
```

**Parameters:**

- `paramVec` (const CoinParamVec &)
- `name` (std::string)
- `matchNdx` (int &)
- `shortCnt` (int &)

### `lookupParam`

Look up the command keyword (name) in the parameter vector. Print help if requested.

```cpp
COINUTILSLIB_EXPORT int lookupParam(std::string name, CoinParamVec & paramVec, int * matchCnt = 0, int * shortCnt = 0, int * queryCnt = 0)
```

**Parameters:**

- `name` (std::string)
- `paramVec` (CoinParamVec &)
- `matchCnt` (int *)
- `shortCnt` (int *)
- `queryCnt` (int *)

### `printIt`

Utility to print a long message as filled lines of text.

```cpp
COINUTILSLIB_EXPORT void printIt(const char * msg)
```

**Parameters:**

- `msg` (const char *)

### `shortOrHelpOne`

Utility routine to print help given a short match or explicit request for help.

```cpp
COINUTILSLIB_EXPORT void shortOrHelpOne(CoinParamVec & paramVec, int matchNdx, std::string name, int numQuery)
```

**Parameters:**

- `paramVec` (CoinParamVec &)
- `matchNdx` (int)
- `name` (std::string)
- `numQuery` (int)

### `shortOrHelpMany`

Utility routine to print help given multiple matches.

```cpp
COINUTILSLIB_EXPORT void shortOrHelpMany(CoinParamVec & paramVec, std::string name, int numQuery)
```

**Parameters:**

- `paramVec` (CoinParamVec &)
- `name` (std::string)
- `numQuery` (int)

### `printGenericHelp`

Print a generic how to use the command interface help message.

```cpp
COINUTILSLIB_EXPORT void printGenericHelp()
```

### `printHelp`

Utility routine to print help messages for one or more parameters.

```cpp
COINUTILSLIB_EXPORT void printHelp(CoinParamVec & paramVec, int firstParam, int lastParam, std::string prefix, bool shortHelp, bool longHelp, bool hidden)
```

**Parameters:**

- `paramVec` (CoinParamVec &)
- `firstParam` (int)
- `lastParam` (int)
- `prefix` (std::string)
- `shortHelp` (bool)
- `longHelp` (bool)
- `hidden` (bool)

## Source

Header: `layer-0/CoinUtils/src/CoinParam.hpp`
