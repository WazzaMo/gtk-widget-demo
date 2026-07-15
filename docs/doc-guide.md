# Doc Guide

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

## Format

Markdown is a text file format that should be as readable as a text file
and only made "nicer" to read when rendered as HTML or other manner.

# Principles

1. Use heading levels 1 to 4 (#) to (####) and use level 1 for new sections,
   not only the title, so the title introduces a new section and should
   have a level 1 heading.
   Vertical space is needed around headings for clarity, meaning empty carriage
   return before and after headings.

2. Space out the file around headings and between paragraphs so that
   the file does not get cluttered. Place an empty line after a heading.

3. Use Mermaid for images where they add value

4. Use headings instead of **highlight**.

5. Try to format the table so it looks clear in the markdown text file.

6. Tables communicate better when a category or label is being described when the row is shorter than 60 chars.
    For long rows, use the next level 3 or heading (### or ####) with long-form text, one or more
    paragraphs below the heading, which allows for more items to be added.

7. Space out bulleted or numbered lists, so they are easier to read.

# Table example

| Category | Description          |
|----------|----------------------|
| Note 1   | make it easy to read |

... and...

# Long Form text

Using a level 4 heading gives more room for lengthier answers.


... is better than

# Labelled line

List of labelled infos:

1. **Note1:** Not easy to read as a text file.

# Purposeful Markdown

Documentation is organised under `docs/`. The layout below shows which
directories exist now and which are planned.

| Directory | Status |
|-----------|--------|
| `docs/notes` | Existing |
| `docs/features` | Existing |
| `docs/release-notes` | Planned |
| `docs/stories` | Planned |

AI agents should start with [AGENTS.md](../AGENTS.md) at the repository root,
which links to this guide and the other convention docs.

## Notes

Notes can have one of the following kinds...

{kind} in the convention below refers to one of these.

1. plan - ideas, concerns and risks for implementing a feature, epic or a user story.
2. coding - a summary of what code changes were recently made.
3. bug - a bug that was found that needs to be addressed, the root cause and acceptance criteria
4. todo - a deferred thought or path for exploration
5. concern - a question that explores a possible limitation and may result in a plan or coding change.
6. test - unit or integration tests that were added with a summary of coverage and pass rate.
7. other - when nothing else fits


Notes are held in the `docs/notes` directory and follow this document guide for formatting.
Notes and features should use a `## Copyright` block after the title, matching the
convention in the core docs.
A note should be prefixed with the date in YYYY-MM-DD format, the kind (above) and have
a meaningful name indicating the essential topic of the note.

This means that notes should follow the naming convention docs/notes/{YYYY-MM-DD}-{kind}-{meaningful-short-name}.md

This way notes will be more unique and easy to understand when they were
produced in the planning and development cycle.


## Release Notes

Release notes are held in `docs/release-notes` and follow the formatting rules in this document
guide. Their naming convention is `{semver}-Release-{date}.md` where semver means
semantic versioning with Major.Minor.Revision numbers and date is in YYYY-MM-DD
format. For example: `1.0.0-Release-2026-07-12.md`.

Describe what new features were added in the commits that resulted in this release.

Release notes can collect information from a sequence of notes (docs/notes) where there are
notes of kinds in a series:
1. [todo] -> [plan] -> coding -> test to flag
  - what work was completed, where [x] was an optional kind step; and
2. bug -> test
  - to collect information about bugs found and fixed.


## Features

For product-led engineering, features can be described and documented
in a way to focus on consistent definitions with use cases
and acceptance criteria that gives intent around user impact.

They will be found in `docs/features`.

Feature files follow the naming convention
`docs/features/feature-{n}-{short-name}.md`, where `{n}` is a sequential number
and `{short-name}` describes the feature topic. For example:
`docs/features/feature-1-basic-editing.md`.

Each feature should include use cases and acceptance criteria.

## Epics and Stories

User stories may be created in the project when breaking down
features into smaller, buildable components.

These are to be written into `docs/stories/`.

Write requirements to `docs/stories/{epic|story}-{feature-name}-{component}-{description}.md`,
using either `epic` or `story` as the prefix. For example:
`docs/stories/story-basic-editing-file-explorer-tree-view.md`.

Stories should be used to take the intention written in a feature
and turn it into a set of epics and stories that should be used
as the context to engineer a single component of the whole feature,
which is part of the final system.

## Bugs

Some AI subagents are directed to find bugs during unit and integration
testing and work to validate that the bugs are repeatable.

When bugs are found, write it up as a bug note (see kind above) using the
general naming convention: `docs/notes/{YYYY-MM-DD}-bug-{short-description}.md`

It should cover:

  1.  symptoms of failure - what went wrong? what definition says this is wrong?
  2.  can it be repeated from command line execution?
  3.  can independent tests be added that find the same problem?
  