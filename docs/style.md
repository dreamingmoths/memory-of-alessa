# Memory of alessa styling guide

This is a styling guide for Silent Hill 2 & 3 repository, styling is not final if another styling is needed for matching or strings hint a style used by the developers, but it should be used in general to keep a standard in the codebase

## Types
Follow the standard from `eetypes.h`, types used should be `sign_type` (`u_char`, `s_char`, `u_long`, `s_long`, etc.) for non floating point primitive types (`int` can be used without its signed counterpart)

## Formatting
There is a `.clang-format` file that can be applied to format the file, do note that clang-format trims empty whitespace lines, so it should be used carefully in files where DWARF line info matters

You can check the file to see which clang-format values it has, each option can be searched [here]("https://clang.llvm.org/docs/ClangFormatStyleOptions.html") for more information:

- Pointer Alignment: Left
- Indentation Width: 4
- Comments aligned

### Function declarations & definitions
Empty arguments in functions should have `(void)` in its prototype and `()` in its definition. Omitting the `void` from the prototype might cause mismatches after linking, even if the compilation output matches

### File ending
Files should end with a newline for *nix-like systems compatibility

### Extra parentheses
Unless readability is improved by adding extra parentheses, only the necessary ones should be used


### Explicit conditionals

Unless it improved readability/is necessary for matching, conditionals should be written as simple as possible:


Example 1:

```
if(exampleVar != 0){
    //code..
}
```
can be converted to
```
if(exampleVar){
    //code..
}
```

Example 2:

```
if((myVar & 0x8) == 0){
    //code..
}
```
can be converted to

```
if(!(myVar & 0x8)){
    //code..
}
```

Strings in the codebase may hint an specific style used by the developers, this styling is then preferred over the styling guides (eg. `((u_int)data & 0x8) == 0`) 

### NOT bitmasks

Usually the compiler will optimise any `foo & ~0xXXX` bitmask, if such bitmask is detected it should be changed to the `NOT` version:

```
exampleVar &= 0x0xDFFFFFFF
```
should be changed to
```
exampleVar &= ~0x20000000
```

### Increments

Unless necessary for matching, `foo+=1` should be avoided, instead use `foo++`

## Naming

Most of the naming standard only applies to Silent Hill 3's files that are not shared with Silent Hill 2, as SH2 has DWARF info with original names for the majority of the names

### Typedefs from structs
In Silent Hill 2, its DWARF info does not keep typedefs, typedefs can be made based on the preserved naming of the struct:

**Anon structs do not preserve the original name in the DWARF, this does not apply**

_This struct gotten from the DWARF_:
```
struct _IXY {
    // Members
    signed int x; // offset 0x0, size 0x4
    signed int y; // offset 0x4, size 0x4
};
```

_Can be typedef'd to_:
```
typedef struct _IXY{
    // Members
    signed int x; // offset 0x0, size 0x4
    signed int y; // offset 0x4, size 0x4
}IXY;
```

You can then use it in variables without specifying the type keyword (eg. `struct _IXY* foo` -> `IXY* foo`)

### Naming unknown members
Unknown members in struct will follow the `unkXXX` styling, `XXX` being the offset in the struct, for padding to the next member, you should use `u_char unkXXX[0xNUM]`:

```
typedef struct _ExampleStruct{
    u_char unk0[0x4];
    u_short unk4;
    u_short example;
    float unk8;
}ExampleStruct;
````

### Naming styles 
For preprocessor defines, it should use the `SCREAMING_SNAKE_CASE` style (eg. `#define GET_BIT(x, i) (((x) >> (i)) & 1)`)
For flags defines, it should follow the `1 << XXX` style

## Number formats

### Decimal
- Colors
- Timers
- Array accesses
- Sizes

### Hexadecimal
- Addresses
- Bitmasks

### Booleans

Any boolean should use `TRUE` or `FALSE` instead of `1` or `0` 
