# Fuzz Testing Demonstration

This is a simple demonstration for how to fuzz-test a C++ program with the AFL ("American Fuzzy Lop") fuzz tester.

![AFL screen shot](afl.png)

## What is fuzz testing?

The goal of unit tests is to feed well-known input into your program and compare its output to the expected results.

The goal of fuzz tests is to feed random data into your program until it crashes.

## Running the demonstration program

The demonstration program consists of an (intentionally buggy) implementation of a URI decoder function and a simple main function that calls it with input read from stdin. A URI decoder converts hex sequences like `%2f` into the appropriate characters (in this case, `/`).

### Build The Program

```sh
$ cd build
$ cmake ..
$ make
```

### Try It Out

The afldemo program reads URI encoded input from stdin and decodes it to stdout.

```sh
$ ./afldemo <<<Hello+World%21
Hello World!
```

## Fuzz-Testing The Demonstration Program

Replace `2.49b` by the appropriate version of AFL (that is, what afl-latest.tgz unpacks into).

### Download And Build AFL

```sh
$ mkdir afl
$ cd $_
$ wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
$ tar xzf afl-latest.tgz
$ cd afl-2.49b/
$ make
```

### Create Initial Test Cases

To get AFL started, give it some legal input that your programm processes. Create one file per input string in the `testcases`directory.

```sh
$ cd afl-demo
$ mkdir testcases
$ cd $_
$ echo your test input >name.txt
```

### Build The Instrumented Test Program

```sh
$ cd afl-demo
$ mkdir aflbuild
$ cd $_
$ CC=/path/to/afl/afl-2.49b/afl-gcc CXX=/path/to/afl/afl-2.49b/afl-g++ cmake ..
$ make
```

### Run The Fuzz Test

```sh
$ cd afl-demo/aflbuild
$ /path/to/afl/afl-2.49b/afl-fuzz -i ../testcases -o ../findings ./afldemo
```

Or, when using this demonstration project, use the provided shell script that builds the instrumented test program and runs the fuzz tester. Edit `fuzz.sh` first and set variable `AFL` to the directory in which you built AFL.

```sh
$ cd afl-demo
$ ./fuzz.sh
```

### Evaluating Test Results

Let the fuzz tester run until it found one or more crashes. Find the input that made the program crash in the `findings/crashes` directory. Debug and fix your program until it processes the input cleanly (it may be a good idea to add AFL's findings to your suite of unit tests). Repeat until no more crashes are foud.

## Resources

AFL homepage: http://lcamtuf.coredump.cx/afl/

About fuzz testing: https://en.wikipedia.org/wiki/Fuzzing

The OSS Fuzz project: https://github.com/google/oss-fuzz

---
*Wolfram Rösler • wolfram@roesler-ac.de • https://twitter.com/wolframroesler • https://github.com/wolframroesler*

