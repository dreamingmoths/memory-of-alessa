# dwarf quirks
 
The SH2 Prototype this project aims to match contains debugging information which aid in the decompilation of both SH2 and SH3. Unfortunately, said debugging information contains a few quirks as a result of the compiler. This document attempts to record observed quirks in the prototype's debugging information. 

## Functions and local variables

### Inversely-ordered local variable declarations
Local variable declarations are inverted in the DWARF. Take for example:

```c
u_int foo(int bar) {
	int a;
	int b;
	int c;
	...
}
```

This would come out in the DWARF as:

```c
unsigned int foo(signed int bar /* r16 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
        signed int c; // r5
        signed int b; // r2  
        signed int a; // r3
    }
}
```

If you have the SH2 DWARF in hand, try comparing the declarations of `ThreadPad` from [this scratch](https://decomp.me/scratch/URKra) with the declarations in the DWARF.

> Note: This was fixed in later versions of MWCC.

### Omission of the static qualifier in local variables
When a local variable is declared as static, the static qualifier will be omitted from the variable and an address will be provided next to it. For example:

```c
int foo(int bar) {
	int x;
	static int a[2];
	...
}
```

This will come out in the DWARF as

```c
signed int foo(signed int bar /* r16 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
        signed int a[2]; // @ 0x0DEFACED
        signed int x; // r2
    }
}
```

See [this scratch](https://decomp.me/scratch/cLsKq) and its fork for a practical example.

### Omission of unused arguments
Function arguments are omitted if they go unused within the function itself. For example:

```c
int foo(int x, int y, int z) {
	...
}
```

If `y` goes unused, it will be omitted and the function will be represented in the DWARF like so:

```c
signed int foo(signed int x /* r16 */, signed int z /* r17 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
    }
}
```

See `loadBgAll_SetLoadRequestIndoor2x2` in [this scratch](https://decomp.me/scratch/Lzj5X) for a practical example.

### Omission of unused local variables
If a local variable goes unused, it will be omitted. For example:

```c
int foo() {
	int bar;
	int baz;
	...
}
```

if `baz` goes unused, the function will show up in the DWARF like so:

```c
signed int foo() {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
        signed int bar; // r2
    }
}
```

Pragmatically speaking, variable omission usually occurs as a result of variables being optimized out. For example, if one copies the code from [this scratch](https://decomp.me/scratch/DtIz7) to [this scratch,](https://decomp.me/scratch/jCQz3) the compiler will output equivalent assembly despite the introduction of an additional variable. The DWARF also remains equivalent:

```
# Scratch's DWARF
TAG_local_variable - i,   s2
TAG_local_variable - lp,  s0
TAG_local_variable - kfp, s1
TAG_local_variable - obj, s0

# Original DWARF
TAG_local_variable - i,   s2
TAG_local_variable - lp,  s0
TAG_local_variable - kfp, s1
TAG_local_variable - obj, s0
```

(kudos: [Mc-muffin](https://github.com/Mc-muffin))

### Struct arguments as local variables
When a function has a struct for an argument, it will appear as a local variable. For example:

```c
typedef struct {
	int x;
	int y;
	int z;
} coord;

void set_pos(int x, int y, int z, coord position) {
	...
}
```

This will come out in the DWARF as:

```c
void set_pos(signed int x /* r2 */, signed int y /* r2 */, signed int z /* r2 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
    		struct /* @anon1 */ {
    			signed int x; // offset: 0x0, size: 0x4
    			signed int y; // offset: 0x4, size: 0x4
    			signed int z; // offset: 0x8, size: 0x4
    		} position; // r29
    }
}
```

The same goes for named structs.

```c
typedef struct coord {
	int x;
	int y;
	int z;
} coord;

void set_pos(int x, int y, int z, coord position) {
	...
}
```

This will come out as:

```c
void set_pos(signed int x /* r2 */, signed int y /* r2 */, signed int z /* r2 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
    		struct coord position; // r29
    }
}
```

Struct pointers are not affected by this.

See [this scratch](https://decomp.me/scratch/3KRij) and compare it to the DWARF for a practical example.

### Multiply-defined local variables

Scopes aren't taken into consideration in the debug info. As a result, all local variables will appear at the start of a function. In some cases, this can cause variables to be declared twice. For example:

```c
int foo(int bar) {
	int offset;
	...
	if (offset < 0) {
		int size;
		...
	} else {
		int size;
		...
	}
	...
}
```

This will come out in DWARF as:

```c
signed int foo(signed int bar /* r2 */) {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0xDEADBEEF
        signed int size; // r3
        signed int size; // r3
        signed int offset; // r16
    }
}
```

See [this scratch](https://decomp.me/scratch/UGzq7) and its forks for a practical example.

> Note: Scoped declarations aren't specific to similarly-named variables. See [this scratch.](https://decomp.me/scratch/CqUW2)

### Fake namespaces
> Note: this is a quirk of Ghidra & DTK, not DWARF. Documented anyway to clear any confusion that might occur when observing the DWARF

When a function has a struct pointer for an argument and said pointer is named `this`, DTK and Ghidra will incorrectly output the function as though it belonged to a namespace with the struct's name in the DWARF. For example:

```c
typedef struct foo {...} foo;

void foobar(foo* this) {...}
```

DTK will output the function as
```c
// this: r2
void foo::foobar() {
    /* anonymous block */ {
        // Range: 0x00000000 -> 0x0D15EA5E
    }
}
```

Unlike DTK, Ghidra will keep the function parameter.
```c
void foo::foobar(foo* this)

{ ...
```
non-typedef'd and anonymous structs are not immune to this.

Look for `SubCharacter::EnemyEDBFunction` in the DWARF or Ghidra for a practical example.

(TODO: consider moving this to its own section if another tool quirk occurs)
## Global variables

### Unused global variables
Unlike local variables. global variables are not omitted from the DWARF if they go unused. Instead, they'll remain and will be assigned an address of zero. For example:
```c
int drinks = 0;
static int cards = 0;
static int seals = 0;
```

If `cards` goes unused, the following variables will come out in the DWARF like so:
```c
signed int drinks; // size: 0x4, address: 0xDEADDEAD
static signed int cards; // size: 0x4, address: 0x0
static signed int seals; // size: 0x4, address: 0xDEADD00D
```
This behavior changes based on whether or not linker dead code elimination is enabled. If it's disabled, the variable will be assigned a regular address.
```c
signed int drinks; // size: 0x4, address: 0xDEADDEAD
static signed int cards; // size: 0x4, address: 0xDEADBEEF
static signed int seals; // size: 0x4, address: 0xDEADD00D
```

Look for `keyhistcnt` in the DWARF for a practical example.

### initialization & BSS ordering 
Uninitialized and zero-initialized global variables both lie in BSS but will have different ordering. For example:

```c
int exec_time;
int sleep_time;
int wake_time;
int total_time;
```
This will come out in the DWARF as:
```c
signed int total_time; // size: 0x4, address: 0x98
signed int wake_time; // size: 0x4, address: 0x9C
signed int sleep_time; // size: 0x4, address: 0xA0
signed int exec_time; // size: 0x4, address: 0xA4
```

But if we zero-initialize them:
```c
int exec_time  = 0;
int sleep_time = 0;
int wake_time  = 0;
int total_time = 0;
```
They'll instead come out as:
```c
signed int exec_time; // size: 0x4, address: 0x98
signed int sleep_time; // size: 0x4, address: 0x9C
signed int wake_time; // size: 0x4, address: 0xA0
signed int total_time; // size: 0x4, address: 0xA4
```
Notice how the declaration order has been reversed.

Try comparing `sh2gfw_SyncDBG`'s declarations in the repo with the declarations in the DWARF for a practical example.

### Omission of the static qualifier in file-scoped variables
If a file-scoped static variable is referenced before being initialized, MWCC will omit its static qualifier from the DWARF. For example:
```c
static int steps = 0;
int foo() { steps++; ...}
```
This will come out in the DWARF with the static qualifier.
```c
static signed int steps; // size: 0x4, address: 0x84
```
But if we remove the zero-initialization:
```c
static int steps;
int foo() { steps++; ...}
```
It'll come out as:
```c
signed int steps; // size: 0x4, address: 0x84
```
This doesn't necessarily mean that the variable will be treated as a global; the symbol table will still define the variable with a local scope.
```
                        *** SYMBOL TABLE (.symtab) ***

no     value       size        bind    type     other      shndx          name

1      0x00000084  0x00000004  LOCAL   OBJECT   DEFAULT    MAIN           steps
...
```

Try comparing `dma1cmd`'s declaration of `last_regist_cid` in the repo with its declaration in the DWARF for a practical example.
