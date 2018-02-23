# 42sh
[![Build Status](https://travis-ci.org/uael/42sh.svg?branch=master)](https://travis-ci.org/uael/42sh)

## Mandatory part:
- [x] Prompt without line edition.
- [x] Builtins `cd`, `echo`, `exit`, `env`, `setenv`, `unsetenv` with there options.
- [x] Executing simple commands with there parameters using `PATH`.
- [x] Support for redirection `>`, `>>`, `<`and `|`.
- [x] Logical operand `&&`and `||`.
- [x] Separator `;`.

## Optional feature (five of theses are mandatory to validate the project):
- [x] Inhibitors `"`, `'`and `\`.
- [x] Advanced redirections: aggregation of file output and heredoc `<<`.
- [ ] Globbing: `*`, `?`, `[]`, `{}`, etc.
- [x] Backquotes \`.
- [x] Subshell with operand `()`.
- [x] Local variable and builtin `unset` and `export`.
- [x] History with builtin `history`and `!` with options.
- [x] Advanced line edition.
- [x] File descriptors and builtin `read` with options.
- [x] Dynamical autocompletion.

## Optional feature highly appreciated:
- [x] Job Control and builtins `job`, `fg`, `bg` and operand `&`.
- [X] Shell Scripting: bang (!), variable assignements
