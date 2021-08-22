Utility to track build system file accesses and process invocations

**Usage**
---

```
Usage: buildwatch [OPTIONS] [COMMAND]

Options:
  -h, --help Display this message and exit
  -v         Display version and author information and exit.
```

**Build Instructions**
---

1. Create an output folder for an out-of-source build

2. `cd` to the output folder and invoke cmake with appropriate options.
    - Set `-DADDRESS_SANITIZER=1` or `-DUNDEFINED_SANITIZER=1` to build with
    sanitizers

3. `make`

**Useful Rules**

1. `make clang-format`

2. `make clang-tidy`