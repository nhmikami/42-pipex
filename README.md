# 42-pipex

This project replicates the behavior of shell pipelines in UNIX-like systems, enabling the redirection of input and output streams to facilitate data transfer between processes.<br />

## Description
The program must behave exactly the same as the following shell command, handling a single pipe
```sh
< infile cmd1 | cmd2 > outfile
```
  * `< infile` redirects the contents of `infile` as the standard input (`stdin`) for `cmd1`
  * `cmd1` is the first command to be executed
  * `|` (pipe operator) connects the standard output (`stdout`) of `cmd1` to the standard input (`stdin`) of `cmd2`
  * `cmd2` is the second command to be executed
  * `> outfile` redirects the standard output (`stdout`) of `cmd2` to `outfile`

Run the program:
```sh
./pipex infile cmd1 cmd2 outfile
```

## Bonus
**Handle multiple pipes**
```sh
< infile cmd1 | cmd2 | ... | cmdN > outfile
```

Run the program:
```sh
./pipex infile cmd1 cmd2 ... [cmdN] outfile
```

**Support « and » when the first parameter is "here_doc"**
```sh
cmd1 << LIMITER | cmd2 | ... | cmdN >> outfile
```
  * `<< LIMITER` allows the user to provide input directly in the command line or script, terminating when the word `LIMITER` is encountered
  * `>> outfile` redirects the standard output (`stdout`) of `cmdN` to `outfile`, appending the output to the file instead of overwriting it


Run the program:
```sh
./pipex here_doc LIMITER cmd1 cmd2 ... [cmdN] outfile
```

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./pipex infile "invalidcmd" "wc -l" outfile
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes 
