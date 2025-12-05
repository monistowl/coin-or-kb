+++
title = "Message Handling System"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Message construction: printf-style formatting with type safety
  Severity levels: 0=nothing, 1=fatal, 2=error, 3=warning, 4+=info
  Detail filtering: only print if message detail ≤ handler logLevel

  Output chain: CoinMessageHandler << value1 << value2 << CoinMessageEol
  Supports: int, double, char, string, and custom precision

## Complexity

Message lookup: O(1) by message number
  Formatting: O(message_length)
  Filtering: O(1) severity/detail check before formatting

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinMessageHandler.hpp") }}** - Flexible message handling with severity levels and i18n support

Provides CoinMessageHandler for formatted output with:
- Severity-based filtering (warnings, errors, info)
- Detail/logging levels
- Multi-language support (messages default to US English)
- Output to stdout or FILE pointer
