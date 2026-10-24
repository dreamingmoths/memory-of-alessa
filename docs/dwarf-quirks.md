# Dwarf Quirks

While SH2's DWARF will prove to be very helpful during decompilation, the compiler that generated it has a handful of quirks. This document attempts to record observed quirks in SH2's DWARF. 

---
## Inversely-ordered local variable declarations
MWCC will record local variable declarations inversely to their original declaration order in the DWARF. Take for example:

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

---
## Omission of the static qualifier in local variables
When a local variable is declared as static, the static qualifier will be omitted from the variable and an address will be provided next to it in the DWARF. For example:

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

---
## Omission of unused arguments
MWCC will omit function arguments from the DWARF if they aren't used within the function. For example:

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

---
## Omission of unused local variables
If a local variable goes unused, MWCC will omit it from the DWARF. For example:

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

Pragmatically speaking, variable omission usually occurs as a result of variables being optimized out. See these two scratches: [[1](https://decomp.me/scratch/DtIz7), [2](https://decomp.me/scratch/jCQz3)] Try copying the code from the first scratch and pasting it to the second. Despite the introduction of an additional variable, the scratch will still match. The DWARF will also remain the same:

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

---
## Struct arguments as local variables
When a function has a struct for an argument, it will be represented in the DWARF as a local variable. For example:

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

This will come out in DWARF as:

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

---
## Multiply-defined local variables

MWCC will only record the order in which variable declarations occurred in the DWARF without any regards to scopes. This can cause certain functions to have two local variables with the same name. For example:

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

>Note: Scoped declarations aren't specific to similarly-named variables. See [this scratch.](https://decomp.me/scratch/CqUW2)

---
(TODO: document quirks regarding globals)
