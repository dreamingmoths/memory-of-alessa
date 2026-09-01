# development

Contributions are welcome!

If you're new to decompilation projects, [contributing.md](contributing.md) is
an introduction for beginners.

## monorepo overview

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

Before submitting contributions, we recommend building from clean to ensure
everything is in order.

```sh
make clean # cleans up all generated files
make       # re-runs the build with maximum parallel jobs
```

Since this project is dedicated to Silent Hill 3, why a shared repo?

There are two glaring reasons. First, we don't have symbols for Silent Hill 3,
but we do have symbols for Silent Hill 2 from the 0.10 VW047-U1 prototype
released on July 13th, 2001. This means we have the original names of functions,
structs, data, etc. as they were written. Second, there is significant overlap
in the engine code of the two games. These two facts combined mean referencing
Silent Hill 2 adds crucial missing context when decompiling Silent Hill 3. And
of course, Silent Hill 2 is a lovely game in and of itself.  The prototype is
full of interesting secrets.

If you own a copy of this prototype disc, you may do the following:

1. Place `SLUS_202.28` in the `rom/SLUS_202.28` folder.
2. Copy the contents of the `gx` folder into `rom/overlay`.
3. Make sure all `.bin` files are lowercase. To do this automatically, run `make
   PROJECT=silent-hill-2 overlays-lowercase`.
4. Finally, run the command below.

```sh
make sh2
```

As of June 21st, 2026, this command should also properly link back into a
matching build of Silent Hill 2. It will create assembly files at
`silent-hill-2/config/SLUS_202.28/asm`.

### `alessatool` commands

To make full use of the debug information from Silent Hill 2, we need to add the
line numbers to the assembly. Example:

```sh
make sh2-report
source tools/scripts/env.sh # will make `alessatool` available
alessatool annotate --asm-path silent-hill-2/config/SLUS_202.28/asm/Chacter_Draw/model3_sub_n.s
```

See `alessatool annotate --help` for more information.

There are more commands, for example `alessatool debug` command may be helpful
for troubleshooting issues with the build. Run `alessatool --help` for a list of
all commands.

## general workflow & `make` commands

Usual development can be thought of in two distinct phases:

1. Linking phase. Here we are making sure that the code builds properly and
   links into a matching executable that can run on a PlayStation 2.
2. Diffing phase. In this phase we are decompiling the code, typically with
   [objdiff](https://github.com/encounter/objdiff) when running locally or using
   [decomp.me](https://decomp.me/).

The linking phase is the default as it helps ensure everything is working
correctly. The following commands are recommended during the linking phase.

```sh
make sh3-build
make sh2-build
```

Note that you can get faster, incremental builds by leaving out the `-build`
part of the command, e.g.

```sh
make
make sh2
```

however these will not always work correctly.*

To enter the diffing phase, run one of the following commands to generate the
expected files.

```sh
make sh3-report
make sh2-report
```

Once these files have been generated, you may open the objdiff gui from the root
of the repository. It will watch for changes to the source files and
automatically rebuild as necessary, though changes to any configuration files
such as the Splat YAML will require the report command to be repeated manually.

```sh
# make sure objdiff is on PATH, or pass the full path to the executable
objdiff-linux-x86_64
objdiff-macos-arm64
```

In general, build files for both Silent Hill 2 and 3 can be on disk
simultaneously without overwriting each other, with the exception of the objdiff
configuration that is named `objdiff.json` so it can be easily picked up by
objdiff.

Before submitting or merging a pull request, please ensure the project builds
from a clean environment.

```sh
make clean
make sh2
make sh3
```

Here are some other useful commands.

```sh
make compiler-info > out.log # logs the mwcc help to a file
make linker-info             # logs the mwld help
make overlays-lowercase      # renames overlay filenames
make debug                   # runs `alessatool debug`
make death                   # really resets most things (!?)

make VERBOSE=1               # see what commands are being run
make PROJECT=silent-hill-2   # you may always pass `PROJECT=` instead of `sh2-`
make NPROC=1                 # build without parallelism
```

(*) In particular, `make sh3` will not always work when moving from the diffing
phase to the linking phase, because the linked C objects are different from the
ones used to generate the report. It also may not always detect source file
changes as the Makefile currently only uses dependency (.d) files from Splat and
not the compiler. This is why `make sh3-build` is preferred when speed is not
highest priority.

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
