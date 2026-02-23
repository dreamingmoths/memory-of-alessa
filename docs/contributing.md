# contributing

> ⭐️ This page is an introduction to decompilation. For project-specific
> information, see [development.md](development.md).

> ❓ Questions or corrections? Contributions are welcome, feel free to make a
> GitHub issue.

Matching decompilation aims to write code that compiles into a 100% identical
copy of a target executable file. Once all of the code of a PlayStation 2 game
is in source form, we can make our own changes to the game, or port it to other
platforms such as PC or the Nintendo Switch.

This process requires that you own a copy of the game already. None of the
original game assets or proprietary source files are committed to this
repository.

If you want to get started right away, see the [quickstart](#quickstart) below.
Otherwise, see [how it works](#how-it-works).

## quickstart

To dive right in, use the [setup guide](../README.md) and find an assembly
function in `silent-hill-3/config/SLUS_206.22/asm`. The functions in the `Event`
folder are often small and good for a first attempt. Here's an example of what
we're looking for below.

```s
glabel func_01F6D6C0_heaven_00
    /* C0 01F6D6C0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* C4 01F6D6C4 D301013C */  lui        $at, %hi(D_1D31674 + 0x8)
    /* C8 01F6D6C8 0000BFFF */  sd         $ra, 0x0($sp)
    /* CC 01F6D6CC 7C16238C */  lw         $v1, %lo(D_1D31674 + 0x8)($at)
    /* D0 01F6D6D0 C21E0300 */  srl        $v1, $v1, 27
    /* D4 01F6D6D4 01006330 */  andi       $v1, $v1, 0x1
    /* D8 01F6D6D8 03006010 */  beqz       $v1, .L01F6D6E8_heaven_00
    /* DC 01F6D6DC 0D000424 */  addiu      $a0, $zero, 0xD
    /* E0 01F6D6E0 90B2050C */  jal        func_0016CA40
    /* E4 01F6D6E4 00000000 */  nop
  .L01F6D6E8_heaven_00:
    /* E8 01F6D6E8 0000BFDF */  ld         $ra, 0x0($sp)
    /* EC 01F6D6EC 0800E003 */  jr         $ra
    /* F0 01F6D6F0 1000BD27 */  addiu      $sp, $sp, 0x10
endlabel func_01F6D6C0_heaven_00
```

Visit the website [decomp.me](https://decomp.me) and create a new scratch
there. Paste in the assembly and select the Silent Hill 3 compiler preset.

Now this is the work of decompilation. Try to edit the source file and its
context until the assembly matches. On decomp.me, the `m2c` decompiler will give
a decent starting point, and the goal is to fix all of the errors and mismatches
until it is a 100% match.

## how it works

The following is an overview of how this project was set up, which may be
helpful to understand as you work in the repo.

### step 1: game binary → plaintext assembly files

We need to extract assembly from the file we want to decompile. For this we use
a _disassembler_, this project uses
[spimdisasm](github.com/Decompollaborate/spimdisasm) via
[splat](https://github.com/ethteck/splat).

Splat allow us to describe the structure of our file using a markdown format.
For example, see the Silent Hill 3 project YAML at
[SLUS_206.22.yaml](../silent-hill-2/config/SLUS_202.28/SLUS_202.28.yaml), and
also see the Silent Hill 2 YAML,
[SLUS_202.28.yaml](../silent-hill-2/config/SLUS_202.28/SLUS_202.28.yaml).
Because we have debug information in Silent Hill 2 from a 2001 demo release, the
filenames listed in its YAML are exactly the same as the original filenames
found in that release. These YAMLs help us produce assembly (`.s`) files that
are found in `silent-hill-3/config/SLUS_206.22/asm` and
`silent-hill-3/config/SLUS_202.28/asm`, respectively.

### step 2: assembly files → binary (again)

After _disassembling_ everything, we need to _assemble_ the resulting assembly
(`.s`) files into individual [object (`.o`)
files](https://en.wikipedia.org/wiki/Object_file). These object files should be
able to be stitched back together into something that matches the file we
started with.

For this we use the GNU assembler, `as`, from
[`binutils`](https://www.gnu.org/software/binutils/). This project uses a fork
of `as` found at
[`binutils-mips-ps2-decompals`](https://github.com/dreamingmoths/binutils-mips-ps2-decompals).

Note that no code is involved yet, we haven't compiled any C files.

### step 3: `.o` files → executable file

After successfully splitting the binary apart and assembling each piece, the
_linker_ stitches all the object files back together to create the Silent Hill 3
executable.

The linker this project uses is an old, relatively niche software known as the
Metrowerks linker (MWLD), which pairs with the Metrowerks C compiler (MWCC),
which shipped with the [CodeWarrior
IDE](https://en.wikipedia.org/wiki/CodeWarrior).

If the linker plays nice, then we end up with a file that 100% matches the one
we started with.

### step 4: assembly files → code

Now that we've done this whole dance of diassembling, assembling, and linking,
the decompilation work begins.

A project can often be started by taking just one function out of the binary. In
Splat, we find an assembly split:

```yaml
    - [0x000000, asm, code]
```

and change it to a code split for C (or C++ in other projects):

```yaml
    - [0x000000, asm, code_0]
    - [0x000040, c,   alessa]
    - [0x000080, asm, code_1]
```

This tells Splat that this split is now implemented in C, so it will be compiled
with MWCC instead of assembled from plain assembly.

Now the goal is to write C code that matches (see [quickstart](#quickstart)).
The function is considered _matched_ when we can compile C code into an object
(`.o`) file identical the one we would get via assembling the function's
assembly.

Since this new `.o` file from the C compiler should be interchangeable with the
`.o` file from the assembler, we can use it when linking. If all works out, we
have an identical copy of Silent Hill 3!

### summary

This is a general overview of how the "[Ship of
Theseus](https://en.wikipedia.org/wiki/Ship_of_Theseus)" approach to
decompilation works. We split a game into binary files, and replace those binary
files one-by-one with compiled C code. This guide leaves out a lot of detail and
nuance about topics such as ELF sections (`data`, `rodata`, `bss`, `sdata`,
etc.), symbols, linker scripts, compiler optimizations, etc., but hopefully it
should clear up what the project is about and how it works. It can likely be
improved, please feel free to leave an
[issue](https://github.com/dreamingmoths/memory-of-alessa/issues) if you have
suggestions.


### next steps?

- read [development.md](development.md)
- try matching functions on [decomp.me](https://decomp.me)
- read more about [splat
configuration](https://github.com/ethteck/splat/wiki/Configuration)
