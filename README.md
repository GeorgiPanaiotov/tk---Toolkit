# tk---Toolkit
A collection of native developer tools, packed into an Assembly wrapper.

## Building:
`make build_and_link` can be used to build the **tk** file.

`tk loc .` can be used as an example usage. **tk** is obviously the wrapper call, **loc** is the app to be called, **.** is the input - in this case its the current directory.

## Warning:
Currently developed and tested on Linux.  
  
The project uses POSIX compliant interfaces and mostly Linux-specific behavior.  
Windows is only expected to work through WSL.

## Needed Packages
1. `ghc` preferably version 9.4.7, but I do believe other versions also work. You might encounter problems with the way I have included and linked all the libraries and object files related to Haskell, and might require you to change some of the paths  
2. `gcc` for obvious reasons  
3. `fasm` to compile the final executable  
  
The repo includes already built files for the sake of shipping with precompiled binaries. The main executable is located in the `build` directory, and its called `tk`. **It might require you to give it execute privileges - `chmod +x tk`**.

## Better descriptions of each application and benchmarks
**All benchmarks will be performed on the current codebase of the time of writing**  

- ### tk <app> <input>
tk is the main executable, it is where each other app can be called from. It is written in **Assembly** and acts as the delegator of the whole application

- ### tk loc <input>
loc is the Lines of Code program. Can be used with a directory or a single file as input. If a directory is provided it will recursively walk all the sub-directories and find all the files which it will then parse to give a general output of:
  - Total files checked
  - Total files skipped
  - Total lines of code
  - Code lines
  - Blank lines
  - Comment lines - Doesn't support multiline comments, and currently only supports comments in the style of '//'
  - A table that includes all the languages found, how many lines of code that specific language has, and the number of files of the specific language
The program also completely skips directories like **build**, **bin**, **obj**, **node_modules**

```
tk tm tk loc .
Total files checked: 27
Total files skipped: 1

Total lines of code: 1,739

Code lines: 1,485
Comment lines: 1
Blank lines: 253


Language               Lines of Code    Number of Files
-------------------------------------------------------
C/C++ Header                     364                  7
C                              1,029                 11
Haskell                           72                  1
Other                              1                  1
Make                             110                  6
Assembly                         163                  1
-------------------------------------------------------

-----------------------------------
RAM used: 15.613 MB
Execution time: 0.051265 seconds
-----------------------------------
```

- ### tk tm <app> <input>
tm is the Time program. It takes another app as input and the input to the other app, starts it and measures the time it took for the program to finish execution and gives the peak RAM memory it used

- ### tk mu <input>
mu is the Disk Memory Usage program. It takes a directory, or a single file as input. If a directory is provided, similar to **loc** it will recursively walk the tree and gather information about the sizes. Currently it also performs **open** on files which was left as potential extension for some metadata collecting. Generates output of in the form of table, that includes:
  - Total file size in both space taken on disk, and the footprints
  - Total directory size in both space taken on disk, and the footprints
  - Total combined size in both space taken on disk, and the footprints
It doesn't skip directories
```
tk tm tk mu .
Metric                                       Totals     Footprint Totals
------                                       ------               ------
Total file size                          226.777 KB           328.000 KB
Total directory size                      56.000 KB            56.000 KB
Total combined size                      282.777 KB           384.000 KB

Total files checked                              42


-----------------------------------
RAM used: 15.031 MB
Execution time: 0.056686 seconds
-----------------------------------
```

- ### tk relf <input>
relf is the Read ELF program. It takes a file as input and produces a very small (at the time of writing this) output. It parses just a few fields from the header at that point. The process of re-writing the parsing has begun in **Haskell**. There is going to be further parsing which would take into account the full file, but for now it isn't implemented yet

```
tk tm tk relf ./build/tk
         ELF Header:

MAGIC                          7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
CLASS                          ELF64
DATA                           Little Endian
VERSION                        1 (current and original)
OSABI:                         UNIX - System V
ABI VERSION                    0
TYPE:                          EXEC Executable File
MACHINE                        AMD x86-64
VERSION                        0x1
ENTRY ADDRESS                  0x00401260

-----------------------------------
RAM used: 18.551 MB
Execution time: 0.066528 seconds
-----------------------------------
```

- ### tk psm <input>
psm is the Process Sandbox Manager program. At the time of writing it does nothing other than greet you with a simple 'Hello, World!'. It is planned for it to become a very lightweight process starter - similar to **Docker**.
