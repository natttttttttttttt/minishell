- `echo $>` -> breaks the exit codes -> cmd_lst is empty afterwards from what i understood

- `> > > > >` -> prints error syntax token stuff several times and also breaks error code

- if you send random shit or invalid permission to < or >
==14415== Warning: invalid file descriptor -1 in syscall close()

- fd still open when there are several redirs in one way but only when there is also a redir the other way (input output heredoc, input input output, input output output, etc) - i kinda fixed it in a very long and dumb way, didn't push that, will look for a better one
```
==17865==
==17865== FILE DESCRIPTORS: 4 open (3 std) at exit.
==17865== Open file descriptor 3: b
==17865==    at 0x49CA53B: open (open64.c:41)
==17865==    by 0x10AE50: exe_input (exe_utils.c:19)
==17865==    by 0x10A166: set_redirs (cmd_exe.c:93)
==17865==    by 0x10DA0B: do_exe (execute_commands.c:47)
==17865==    by 0x10DC28: execute_commands (execute_commands.c:80)
==17865==    by 0x10B984: parse_and_exe (main.c:45)
==17865==    by 0x10BAB0: main (main.c:89)
