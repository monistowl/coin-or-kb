+++
title = "CoinTimer"
description = "This class implements a timer that also implements a tracing functionality."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinTime.hpp"
api_url = "/api/coinutils/CoinTimer.json"
+++

This class implements a timer that also implements a tracing functionality.

<div class="api-link"><a href="/api/coinutils/CoinTimer.json">JSON API</a></div>

## Description

The timer stores the start time of the timer, for how much time it was set to and when does it expire (start + limit = end). Queries can be made that tell whether the timer is expired, is past an absolute time, is past a percentage of the length of the timer. All times are given in seconds, but as double numbers, so there can be fractional values.
The timer can also be initialized with a stream and a specification whether to write to or read from the stream. In the former case the result of every query is written into the stream, in the latter case timing is not tested at all, rather the supposed result is read out from the stream. This makes it possible to exactly retrace time sensitive program execution.

## Public Methods

### `CoinTimer`

Default constructor creates a timer with no time limit and no tracing.

```cpp
 CoinTimer()
```

### `CoinTimer`

Create a timer with the given time limit and with no tracing.

```cpp
 CoinTimer(double lim)
```

**Parameters:**

- `lim` (double)

### `restart`

Restart the timer (keeping the same time limit)

```cpp
void restart()
```

### `reset`

An alternate name for ``

```cpp
void reset()
```

### `reset`

Reset (and restart) the timer and change its time limit.

```cpp
void reset(double lim)
```

**Parameters:**

- `lim` (double)

### `isPastPercent`

Return whether the given percentage of the time limit has elapsed since the timer was started.

```cpp
bool isPastPercent(double pct)
```

**Parameters:**

- `pct` (double)

### `isPast`

Return whether the given amount of time has elapsed since the timer was started.

```cpp
bool isPast(double lim)
```

**Parameters:**

- `lim` (double)

### `isExpired`

Return whether the originally specified time limit has passed since the timer was started.

```cpp
bool isExpired()
```

### `timeLeft`

Return how much time is left on the timer.

```cpp
double timeLeft()
```

### `timeElapsed`

Return how much time has elapsed.

```cpp
double timeElapsed()
```

### `setLimit`

```cpp
void setLimit(double l)
```

**Parameters:**

- `l` (double)

## Source

Header: `layer-0/CoinUtils/src/CoinTime.hpp`
