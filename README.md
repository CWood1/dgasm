# DGASM - The assembler for Data General Novae and Eclipses

A modern, table-driven assembler for the **Data General Nova** and **Eclipse** families of minicomputers.

dgasm is a portable cross-assembler, written in C, leveraging Flex and Bison. It is designed to run anywhere,
and cross-assemble targeting configurable Nova and Eclipse variants.

---

## Quick start

You will need:

- GCC or Clang
- Flex
- Bison
- CMake
- Make

To build dgasm, do the following:

```sh
$ cmake .
$ make
```

---

## Usage (Planned)

```sh
dgasm -t nova4 -o output.bin input.asm
```

---

## Goals

- Provide a clean, maintainable assembler for Nova and Eclipse systems
- Support multiple CPU variants via selectable target
- Run portably on modern machines

---

## Supported Architectures (Planned)

The following base architectures are planned. This list may grow in the future.

- Nova 1
- Nova 3
- Nova 4
- Eclipse S/140

---

## Important Features
### Address space layout

Data General machines have requirements for variable emplacement, that makes programming directly challenging:

* For Novae, all variables must be within +/- 127 of either the program counter, AC2, or AC3, or must be in the zero page.
* For Eclipses, variables that meet the above rules have a shorter instruction coding than variables that do not.
* Some locations in the zero page are auto-incrementing or auto-decrementing, when accessed indirectly.

Address space layout allows the programmer to instruct dgasm to declare a variable somewhere, and lay it out optimally, as it
sees fit. This may be interspersed with code, or live in the zero page, or elsewhere altogether.

Likewise, it allows the programmer to mark certain variables as autoincrement/autodecrement, managing emplacement accordingly.

Note that the more restrictive the layout (ie, the more the programmer defines where things live on an address level), the fewer
options the compiler has to resolve address space layout. The more restrictive it is, the higher the chance address space layout
will fail, and the programmer may have to define things by hand.

---

## Current status

Proof of concept and project inception. Nothing exists yet really.

---

## Design Philosophy

dgasm is designed with modern conveniences in mind. The architecture is fairly traditional for an assembler:

1. Lexical analysis
2. Parsing
3. Semantic validation and encoding
4. Multi-pass symbol and const resolution
5. Address space layout and validation
6. Binary emission

dgasm provides conveniences such as variable emplacement, assemble-time const expressions, etc to aid in the
development process.

Instruction encoding is table driven, to facilitate easy extension of the assembler.

---

## Roadmap

Short term:

* Instruction encoding for core NOVA instructions, and (some) Eclipse S/140 instructions
* Validity checking (test output on actual hardware and simh)
* Address space layout

Medium term:

* Full support of architectures planned
* Multi-file support using imports
* Full macro processor
* Conditional preprocessing

Long term:

* Support for Data General OSes - RDOS, AOS, possibly AOS/VS

---

## Contribution

Contributions are very welcome.
