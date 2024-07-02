# lc is a simple line counter
-----------------------------

## How build

### build the objects

```bash
gcc -c explorer.c -o explorer.o
```

```bash
gcc -c lc.c -o lc.o
```

### build the programm

```bash
gcc explorer.o lc.o -o lc
```

## How use

If you call ./lc with no arguments this use the current path, count lines on each file (.git folder and executables are excluded from counting).
You can pass a custom path to start explorer. Exemple:

```bash
./lc ./foo
```

This tell to the program to start explore from foo directory.
