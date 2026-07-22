# C Code Standard

C is a beautifully small and simple language.

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Code organisation

Many small files are preferred over fewer, larger files.
Smaller files are easier to navigate and can have meaningful filenames,
so code is easier to find.

The project base directories for source code:

- source: `src/`
- headers: `include/`

C being smaller in both keywords and concepts, requires more code
to cover the same functional ground compared to higher-level languages.
This means we need a strategy for handling many small files.

## Main entry point

The main entry point should be located at `src/main.c` so that it
exists outside any code groups. It should refer to other source
code that exists within groups to compose the program.

## Arranging code in groups

For clarity code can be arranged in groups which represent an area
of functionality that has a natural relationship.

Groups should have a top-level include file that includes the separate
declaration files. This provides convenience but also makes code
navigation easier.

Let's define terms to make this organisation clearer.
Groups should have a meaningful GROUP-NAME and the top-level include
file should be `include/<GROUP-NAME>.h` so when a C file is using the
group, it's easy to specify and read.

The group's declaration details need to be in many small files, not
a single large one, so the many small include files need to be in
a common directory and that should be `include/<GROUP-NAME>/<UNIT-NAME>.h`
where the UNIT-NAME is one implementation UNIT of the group.

The source code should be organised in groups with multiple units:
`src/<GROUP-NAME>/<UNIT-NAME>.c`

The C file units by their UNIT-NAME should correspond to the include
file UNIT-NAME include, declaration files.

### Example - file management

As an example, for a group that implements file management, the following structure could be adopted:

include/file-management.h
include/file-management/
include/file-management/file-objects.h
include/file-management/directory-ops.h
include/file-management/file-read-ops.h
include/file-management/file-write-ops.h

src/file-management/file-objects.c
src/file-management/directory-ops.c
src/file-management/file-read-ops.c
src/file-management/file-write-ops.c

## Unit tests

Unit tests for the groups and their unit should be present in the
`test/` directory and should be organised by groups and units, so
the convention is consistent.
