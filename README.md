# PersonalFinance


This projects's goal is to automate my personal financial calcuations.

## Getting Started as a developer

To begin first navigate to `tools/bash` and type

```bash
$ pip install --editable .
```
in order to install the developer command-line interface (CLI). You might want to add the line
```bash
"$(_FINANCEC_COMPLETE=source Finance)"
```
to your `~/.bashrc` or `~/.bash_profile`.


Move back to this projects root folder. 

To run the code first you must do the standard configure, build, and installation steps

```bash
$ Finance configure
$ Finance build
$ Finance install
```

You may type `$ Finance --help` to see the other CLI options, and you can view the project's build 
configuration options by `Finance configure --help`.



