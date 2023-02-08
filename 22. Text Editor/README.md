# 22.  Text Editor

## Overview 

<ins>__Language__</ins>: C 

<ins>__Completed on__</ins>: February 7th, 2023

Kilo is a small text editor written in under 1K lines of C in a single file with no dependencies &mdash; featuring syntax highlight and search functionalities. 

Keys:

```
CTRL-S: Save
CTRL-Q: Quit
CTRL-F: Find string in file (ESC to exit search, arrows to navigate)
```

Implementation was guided by [this](https://viewsourcecode.org/snaptoken/kilo/index.html) instruction booklet, which is largely based on [Antirez's "Kilo"](http://antirez.com/news/108) &mdash; source code available [here](http://github.com/antirez/kilo).


## To Do

This program is fully implemented and tested. However, code legibility could be improved by commenting `kilo.c`.

## Usage

Upon moving to the current working directory, compile `kilo.c` by running the following command:

```
cc kilo.c -o kilo
```

If no errors occur, this will produce an executable named kilo. 

Alternately, using the Makefile, you can simply run:

``` 
make kilo
```

Then, to run `kilo`:

``` 
./kilo <filename>
```

All saved text will be found at the specified filename.