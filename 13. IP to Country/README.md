# 13.  IP to Country 

<p align="center">
<img width="470" alt="IP Address to Location" src="https://i.ytimg.com/vi/hv8dTJWqdis/hqdefault.jpg"> 
</p>

## Overview 

<ins>__Language__</ins>: Go 

<ins>__Completed on__</ins>: February 3rd, 2023 &mdash; PRESENT (Incomplete)

<b>IP2Country</b> is a lookup tool that accepts .txt or .dat files containing IP address information, and returns any corresponding geographical metadata (*e.g.* country, province, city, zone). 

The program is supported by Golang's ["iphelper"](https://github.com/safing/portmaster) package &mdash; touting buffered I/O functionalities and both JSON and binary encoding. 

Adapted from [JohnTech-O's Git repo](https://github.com/johntech-o/iphelper).


## To Do

IP2Country is still a work in progress! Its implementation is not complete yet, and it also needs to be extensively tested and debugged.

- Currently failing test case TestQuery in "IP2Country_test.go." The file is not parsed properly, and is reaching EOF when reading in its 4-byte header buffer.
- After debugging, need to figure out output format. 

## Usage

Run IP2Country with Go on the command line. The program takes a single command line argument &mdash; the input file's name (can be of form .dat or .txt). 

When ran, it should look something like this:

```
$ go run IP2Country.go input.txt
```

In order to run tests at the command line, run the `go test` command.

```
$ go test 
PASS
ok     shorturl.at/glxDG  0.364s

$ go test -v
=== RUN   TestCreate
--- PASS: TestCreate (0.00s)
=== RUN   TestQuery
--- PASS: TestQuery (0.00s)
PASS
ok    shorturl.at/glxDG  0.372s
```

The implementation and formatting of IP2Country's output is still not completely determined yet, but I will update its usage information here as soon as I have a chance to sort that out. 