# C Code Standard

C is a beautifully small and simple language and it is well-served with
small and simple source files that are organised cleanly and clearly.

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Code organisation within source files

The content of source files should remain easy to extend and maintain.
This means recognising the author of a source contribution, handling multiple
header file inclusions and conventions for header inclusion order, to name
a few.


## Source code header block

All .c and .h files should carry this header block to declare the copyright
and the license used for the file.

```c
/*
 * (c) Copyright 2026 onwards <AUTHOR>.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */
```

Where AUTHOR is the contributor of the code file contributing the code to the project.
The license is important so that it is consistent with the rest of the project.

## Header include guards

Header files should declare macros to protect against duplicate definitions of the same
data types and functions being seen by the compiler when the same header is included
directly, or indirectly, more than once.

For a given header file where `<HEADER_FILE>` refers to the header file name all capitalised
as the path and name to the file.

```c
#ifndef <HEADER_FILE>_H
#define <HEADER_FILE>_H

// Include directives go here

// Declarations go here...

#endif
```

So for `main/window-shell.h` this would be:

```c
#ifndef MAIN_WINDOW_SHELL_H
#define MAIN_WINDOW_SHELL_H

// Include directives go here

// Declarations go here...

#endif
```

## Inclusion directive order

System header files should be included first to indicate the dependencies of the source file.
Project header files should follow for internal dependencies.

## Coding conventions

### Function declarations in header files

Each function should have Doxygen comment blocks, so that hovering over functions in VS Code
will reveal helpful information about the function. This only needs to appear once for VS Code
and the header files should not bloat too much from this.

```c
/**
 * Inspector pane initializer that writes a helpful message into
 * the inspector pane.
 * @param pane the pane object to populate
 * @return none
 */
void introspection_inspector_pane_display_set_initial_text(
  IntrospectionInspectorPane *pane);
```

### Functions

Function names should be snake case to match the C naming conventions in general like `printf`.
Public function names should reflect the source file organisation {group}_{verb}_{noun} so their ownership
and roles are clear.

Static functions do not need to indicate their ownership, so they should replace the {group} with
a double underscore `__`. This will make them stand out visually.

So in `property-list.c` the static function should appear as:

```c
static gchar *
__format_param_flags(GParamSpec *pspec)
{
    // function body...
}
```

### Type declarations

Defined types should have pascal case identifiers, with a group prefix.

## File naming

File names and group directory names should be kebab-cased such as `data-processing/file-handling.h`.

Test files should appear within the `test/` directory from the project root and should be organised
in Group, Unit where:
- Group means the group from the source and header area.
- Unit means the code unit (e.g. main.c) that is under test.

And so for the test file validating signal lists within the introspection Group
for the signal-list Unit, the file name and path would be `test/introspection/signal-list.c`.

GTest case paths (e.g. /introspection/signal-list/gtk-button)
Linking test executables to source units via `meson.build`.
Test static helpers should use the same `__` prefix.

# Organising source files

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

## Arranging code in groups and subgroups

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

Subgroups allow a unit to be broken down where needed to keep source files
smaller and to promote function reuse. Applying this results in files and directories like this:

`src/<GROUP-NAME>/<UNIT-NAME>.c`
`src/<GROUP-NAME>/<UNIT-NAME>/<SUB-UNIT-NAME>.c`

This means that the entry points are in the first unit level:
`src/<GROUP-NAME>/<UNIT-NAME>.c`

And, that implementations in that file may call functions in the sub-unit.

When this group and subgroup arrangement is used for `src/main.c` it results
in code that is composed of files in `src/main/` allowing for reuse and keeping files small.

### Example - file management

As an example, for a group that implements file management, the following structure could be adopted:

include/file-management.h
include/file-management/
include/file-management/file-objects.h
include/file-management/file-read-ops.h
include/file-management/file-write-ops.h
include/file-management/directory-ops.h
include/file-management/directory-ops/list-dir-ops.h
include/file-management/directory-ops/stat-files-ops.h

src/file-management/file-objects.c
src/file-management/file-read-ops.c
src/file-management/file-write-ops.c
src/file-management/directory-ops.c
src/file-management/directory-ops/list-dir-ops.c
src/file-management/directory-ops/stat-files-ops.c

## Unit tests

Unit tests for the groups and their unit should be present in the
`test/` directory and should be organised by groups and units, so
the convention is consistent.
