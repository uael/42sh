# 42sh
[![Build Status](https://travis-ci.org/uael/42sh.svg?branch=master)](https://travis-ci.org/uael/42sh)

## Subject:

[Subject](https://cdn.intra.42.fr/pdf/pdf/183/42sh.fr.pdf)

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
- [x] Globbing: `*`, `?`, `[]`, `{}`, etc.
- [x] Backquotes \`.
- [x] Subshell with operand `()`.
- [x] Local variable and builtin `unset` and `export`.
- [x] History with builtin `history`and `!` with options.
- [x] Advanced line edition.
- [x] File descriptors and builtin `read` with options.
- [x] Dynamical autocompletion.

## Optional feature highly appreciated:
- [x] Job Control and builtins `job`, `fg`, `bg` and operand `&`.
- [X] Shell Scripting: bang (!), variable assignements, brace group, if, while, until, for and functions

## Bonuses
- [X] Advanced dollar expansion `$(..)`, `$((..))`, `$[..]`
- [X] Tilde expansion `~`, `~<username>`, `~-`, `~+`
- [X] Range expansion `{<START>..<END>}` and `{<START>..<END>..<INCREMENT>}`
- [X] Advanced redirections operator `&>`, `&>>`, `<>`, `<<<` and `|&`
- [X] Builtin env advanced options `-u name` and `[name=value]`
- [X] Inline variables `[name=value] binary [arguments...]`
- [X] Binary hashtable
- [X] Rights in the PATH
- [X] Aliases, builtin alias `alias [-p] [name[=value] …]` and expansion

## Usage
```
Usage: ./42sh [option] [script-file] [script arguments...]
ush options:
	--help: this *useful* help message!
ush keymap:
	<ctrl+A|home>: Go to begin of line.
	<ctrl+E|end>: Go to end of line.
	<ctrl+V>: Enter visual mode.
	<ctrl+Y>: Yank in visual mode.
	<ctrl+P>: Paste.
	<ctrl+D>: Exit or delete in visual mode.
	<ctrl+C>: Cancel line edition.
	<ctrl+L>: Clear the screen.
	<shift+[left|right]>: Move per word.
	<shift+[up|down]>: Move per line.
	<up>: Go up in the history.
	<down>: Go down in the history.
	!!: Retype the last command.
	!n: Retype the n command from the begin of history.
	!-n: Retype the -n command from the last command.
	!name: Search for a command beginning with name.
```  
