# PersonalFinance


This projects's goal is to automate my personal financial calcuations.

## For library users

You may now use this library by adding 

```cmake
find_package( PersonalFinance 0.1 REQUIRED )
target_link_libraries( <target> PersonalFinance::PersonalFinance )
```
to your target's `CMakeLists.txt`. If you install the `PersonalFinance` library with the appropriate prefix, you will 
simply need to run cmake with the flag: `-DPersonalFinance_DIR=lib/cmake/personalFinance`.

## Getting Started as a developer

To begin first navigate to `tools/python` and type

```bash
$ pip install --editable .
```
in order to install the developer command-line interface (CLI). You might want to add the line
```bash
"$(_PF_COMPLETE=source pf)"
```
to your `~/.bashrc` or `~/.bash_profile`. For example you may configure the build by the call

```bash
pf configure
```

Move back to this projects root folder. 

To run the code first you must do the standard configure, build, and installation steps

```bash
$ Finance configure
$ Finance build
$ Finance install
```

You may type `$ Finance --help` to see the other CLI options, and you can view the project's build 
configuration options by `Finance configure --help`.



## Personal Notes

I need to fully digest this [reference](https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file)