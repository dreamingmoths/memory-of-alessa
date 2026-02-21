### monorepo overview

The current layout of the project is as follows.

```
silent-hill-3/ --- silent hill 3 project directory
   src/        --- contains the decompiled source code of Silent Hill 3
   config/     --- contains Splat configurations and Splat-generated files including assembly
   include/    --- headers, assembly snippets, linker templates, etc.
silent-hill-2/ --- silent hill 2 engine project directory
   src/
   config/
   include/
include/       --- shared header (.h) files
build/         --- final build output
docs/          --- documentation
rom/           --- contains game files, gets symlinked to `config/<serial>/rom`
tools/         --- shared tooling including compilers, binutils, Python scripts
```

After running `make`, there will be assembly files located at
`silent-hill-3/config/SLUS_206.22/asm`, and final build files are found at
`build/SLUS_206.22`. The build process should link back to a 100% matching ELF
of Silent Hill 3, along with its 40 overlays.

Note the Makefile is a work in progress. You may often need to clean the build
for it to rebuild properly, e.g.:

```sh
make clean # cleans up all generated files
make -j8   # re-runs the build with 8 parallel jobs
```

Since this project is dedicated to Silent Hill 3, why a shared repo?

There are two glaring reasons. First, we don't have symbols for Silent Hill 3,
but we do have symbols for Silent Hill 2 from the 0.10 VW047-U1 prototype
released on July 13th, 2001. This means we have the original names of functions,
structs, data, etc. as they were written. Second, there is significant overlap
in the engine code of the two games. These two facts combined mean referencing
Silent Hill 2 adds crucial missing context when decompiling Silent Hill 3.

If you own a copy of this prototype executable, you may place it as
`SLUS_202.28` in the `rom/SLUS_202.28` folder and run the following command.

```sh
make sh2
```

This will create assembly files at `silent-hill-2/config/SLUS_202.28/asm`. It
will also create build files, but the Silent Hill 2 build does not link at this
time.

### ghidra bsim workflow

[Ghidra](https://github.com/NationalSecurityAgency/ghidra) makes the dual
decompilation approach significantly more viable through its [BSim
plugin](https://ghidra.re/ghidra_docs/GhidraClass/BSim/README.html), which
allows us to search for similar functions. It works like so:

1. Find an interesting function in SH2. Make use of Ghidra BSim to look for a
   similar function in SH3. (Follow the tutorial linked above to get BSim set
   up.)

2. Decompile a function from SH2.

3. Use the result as a starting point for decompiling the SH3 function, editing
   it until it matches.

### more notes

#### more `make` commands

For a local [`objdiff`](https://github.com/encounter/objdiff) workflow, generate
the expected files with the following command.

```sh
make expected
```

There are a couple of ways to clean the SH2 directory.

```sh
# pass the `PROJECT` build argument
make PROJECT=silent-hill-2 clean

# run the alias
make sh2-clean
```

To clean generated files in both projects, run

```sh
make deep-clean
```

or to really delete all setup and reset, run `make death`. This shouldn't be
necessary in most cases though.

#### sh3 compiler flags

```sh
-O3,p -sym=off,noelf -str readonly -sdatathreshold 0
```

#### sh2 compiler flags

```sh
-O2,p -sym=on -str readonly -sdatathreshold 0
```
