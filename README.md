# tk---Toolkit
Assembly wrapper for some developer tools. Each tool can be built as its own standalone application too

## Building:
`make build_and_link` can be used to build the **tk** file.

`tk loc .` can be used as an example usage. **tk** is obviously the wrapper call, **loc** is the app to be called, **.** is the input - in this case its the current directory.

## Warning:
This project might not fit your use case and most certainly will not work on Windows unless started from within `wsl`. It uses POSIX compliant syscalls, but there still might be undefined behavior on UNIX based systems.  
It was tested solely on Linux machines

## Needed Packages
`ghc` is a must due to added Haskell support  
`gcc` for obvious reasons  
`fasm` to compile the final executable  
  
The repo includes already built files for the sake of simplicity
