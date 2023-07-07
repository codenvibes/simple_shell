# **0x16. C - SIMPLE SHELL**
`C`
`Group project`
`Syscall`

# Background Context
Write a simple UNIX command interpreter.

# Concepts
- [Everything you need to know to start coding your own shell]()
- [Approaching a Project](https://intranet.alxswe.com/concepts/350)

# Resources
- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)

man or help:
- `sh` (Run `sh` as well)

# Learning Objectives

<details>
<summary><h3>General</h3></summary>

- Who designed and implemented the original Unix operating system<div>The original Unix operating system was designed and implemented by Ken Thompson, Dennis Ritchie, and others at Bell Labs in the early 1970s.</div>
- Who wrote the first version of the UNIX shell<div>The first version of the Unix shell, known as the "Thompson shell" or "sh", was written by Ken Thompson himself</div>
- Who invented the B programming language (the direct predecessor to the C programming language)<p>The B programming language, which was a direct predecessor to the C programming language, was also created by Ken Thompson.</p>
- Who is Ken Thompson<p>Ken Thompson is a computer scientist and one of the key figures in the development of Unix and the C programming language. He is known for his contributions to the original Unix operating system, the creation of the B programming language, and his work on the development of the Plan 9 operating system and the Go programming language.</p>
- How does a shell work<p>A shell is a command-line interpreter that provides an interface for users to interact with the operating system. It reads commands from the user, interprets them, and executes the corresponding programs or actions. The shell also provides features such as input/output redirection, piping, scripting capabilities, and more.</p>
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of `main`
- How does the shell use the `PATH` to find the programs
- How to execute another program with the `execve` system call
- How to suspend the execution of a process until one of its children terminates
- What is `EOF` / “end-of-file”?
</details>

# Requirements
<details>
<summary><h3>General</h3></summary>

- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 20.04 LTS using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All your files should end with a new line
- A `README.md` file, at the root of the folder of the project is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/alx-tools/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/alx-tools/Betty/blob/master/betty-doc.pl)
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to ([why?](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))
- Write a `README` with the description of your project
- You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see `Docker`
</details>

<details>
<summary><h3>GitHub</h3></summary>

_*There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator. *_
</details>

# More Info

<details>
<summary>

### Output
</summary>

- Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
</details>

<details>
<summary>

### List of allowed functions and system calls
</summary>

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)
</details>

<details>
<summary>

### Compilation
</summary>

Your shell will be compiled this way:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
</details>

<details>
<summary>

### Testing
</summary>

Your shell should work like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
</details>

<details>
<summary>

### Checks
</summary>

The Checker will be released at the end of the project (1-2 days before the deadline). We strongly encourage the entire class to work together to create a suite of checks covering both regular tests and edge cases for each task. See task 8. Test suite.
</details>

# Tasks

<details>
<summary>

### 0. Betty would be proud
`mandatory`
</summary>

Write a beautiful code that passes the Betty checks
</details>

<details>
<summary>

### 1. Simple shell 0.1
`mandatory`
</summary>

Write a UNIX command line interpreter.
- Usage: `simple_shell`

Your Shell should:
- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (`Ctrl+D`)

You don’t have to:
- use the `PATH`
- implement built-ins
- handle special characters : `"`, `'`, <code>\`</code>, `\`, `*`, `&`, `#`,
- be able to move the cursor
- handle commands with arguments

*`execve` will be the core part of your Shell, don’t forget to pass the environ to it…*
```
julien@ubuntu:~/shell$ ./shell 
#cisfun$ ls
./shell: No such file or directory
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ /bin/ls -l
./shell: No such file or directory
#cisfun$ ^[[D^[[D^[[D
./shell: No such file or directory
#cisfun$ ^[[C^[[C^[[C^[[C
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ ^C
julien@ubuntu:~/shell$ echo "/bin/ls" | ./shell
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ julien@ubuntu:~/shell$
```
</details>

<details>
<summary>

### 2. Simple shell 0.2
`mandatory`
</summary>

Simple shell 0.1 +
- Handle command lines with arguments
</details>

<details>
<summary>

### 3. Simple shell 0.3
`mandatory`
</summary>

Simple shell 0.2 +
- Handle the `PATH`
- `fork` must not be called if the command doesn’t exist
```
julien@ubuntu:~/shell$ ./shell_0.3
:) /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls -l /tmp 
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
:) ^C
julien@ubuntu:~/shell$ 
```
</details>

<details>
<summary>

### 4. Simple shell 0.4
`mandatory`
</summary>

Simple shell 0.3 +
- Implement the `exit` built-in, that exits the shell
- Usage: `exit`
- You don’t have to handle any argument to the built-in `exit`
</details>

<details>
<summary>

### 5. Simple shell 1.0
`mandatory`
</summary>

Simple shell 0.4 +
- Implement the `env` **built-in**, that prints the current environment
```
julien@ubuntu:~/shell$ ./simple_shell
$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
julien@ubuntu:~/shell$ 
```
</details>

<details>
<summary>

### 6. Simple shell 0.1.1
`#advanced`
</summary>

Simple shell 0.1 +
- Write your own `getline` function
- Use a buffer to read many chars at once and call the least possible the `read` system call
- You will need to use `static` variables
- You are not allowed to use `getline`

You don’t have to:
- be able to move the cursor
</details>

<details>
<summary>

### 7. Simple shell 0.2.1
`#advanced`
</summary>

Simple shell 0.2 +
- You are not allowed to use `strtok`
</details>

<details>
<summary>

### 8. Simple shell 0.4.1
`#advanced`
</summary>

Simple shell 0.4 +
- handle arguments for the built-in `exit`
- Usage: `exit status`, where `status` is an integer used to exit the shell
```
julien@ubuntu:~/shell$ ./shell_0.4.1
$ exit 98
julien@ubuntu:~/shell$ echo $?
98
julien@ubuntu:~/shell$ 
```
</details>

<details>
<summary>

### 9. setenv, unsetenv
`#advanced`
</summary>

Simple shell 1.0 +

Implement the `setenv` and `unsetenv` builtin commands

- `setenv`
    - Initialize a new environment variable, or modify an existing one
    - Command syntax: `setenv VARIABLE VALUE`
    - Should print something on stderr on failure
- `unsetenv`
    - Remove an environment variable
    - Command syntax: `unsetenv VARIABLE`
    - Should print something on stderr on failure
</details>

<details>
<summary>

### 10. cd
`#advanced`
</summary>

Simple shell 1.0 +

Implement the builtin command `cd`:

- Changes the current directory of the process.
- Command syntax: `cd [DIRECTORY]`
- If no argument is given to cd the command must be interpreted like `cd $HOME`
- You have to handle the command `cd -`
- You have to update the environment variable `PWD` when you change directory

`man chdir, man getcwd`
</details>

<details>
<summary>

### 11. ;
`#advanced`
</summary>

Simple shell 1.0 +
- Handle the commands separator `;`
```
alex@~$ ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn ; ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /var ; ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var ; ls /hbtn ; ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$
```
</details>

<details>
<summary>

### 12. && and ||
`#advanced`
</summary>

Simple shell 1.0 +
- Handle the `&&` and `||` shell logical operators
```
alex@~$ ls /var && ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn && ls /var
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$
alex@~$ ls /var || ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$
```
</details>

<details>
<summary>

### 13. alias
`#advanced`
</summary>

Simple shell 1.0 +
- Implement the `alias` builtin command
- Usage: `alias [name[='value'] ...]`
    - `alias`: Prints a list of all aliases, one per line, in the form `name='value'`
    - `alias name [name2 ...]`: Prints the aliases `name`, `name2`, etc 1 per line, in the form `name='value'`
    - `alias name='value' [...]`: Defines an alias for each `name` whose `value` is given. If `name` is already an alias, replaces its value with `value`
</details>

<details>
<summary>

### 14. Variables
`#advanced`
</summary>

Simple shell 1.0 +
- Handle variables replacement
- Handle the `$?` variable
- Handle the `$$` variable
```
julien@ubuntu:~/shell$ ./hsh
$ ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  snap  spool  tmp
$ echo $?
0
$ echo $$
5104
$ echo $PATH
/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$ exit 
julien@ubuntu:~/shell$ 
```
</details>

<details>
<summary>

### 15. Comments
`#advanced`
</summary>

Simple shell 1.0 +
- Handle comments (`#`)
```
julien@ubuntu:~/shell$ sh
$ echo $$ # ls -la
5114
$ exit
julien@ubuntu:~/shell$ 
```
</details>

<details>
<summary>

### 16. File as input
`#advanced`
</summary>

Simple shell 1.0 +
- Usage: `simple_shell [filename]`
- Your shell can take a file as a command line argument
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode, the shell should not print a prompt and should not read from `stdin`
</details>