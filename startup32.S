/*
  File: startup32.S

  Purpose:  Pass startup argc/argv/envp values to main C code
  on the stack, as done in the standard C library.

  This 32bit assembly code acts as startup code to be run before
  the main C code.  It takes the argc, argv, envp values found
  on the stack at program startup (set up at start-of-execetion
  by the kernel under the execve system call), and pushes them
  onto the stack using the 32bit ABI C calling convention (cdecl),
  for use as arguments by the called function (the main C program).

  This assembly program flows as follows:

    - Execution begins at entry point _start, sanity checks argc value
    - Sets up argc, argv, envp on stack as parameters for called function
      using the 32bit ABI C calling convention (cdecl)
    - Calls mainprog (the C program's main function)
    - Upon return from mainprog, regards %eax as the return code and
      syscalls exit() with exit code = the value returned by mainprog in %eax 
  
  The exectuable C program's main function mainprog() can then access
  these three parameters as arguments passed by the calling function,
  as usual.  No need of using any global variables (in data memory).
*/ 

        .globl  mainprog

        /* Max value for argc is 0x00ffffff = 16M - 1 */
        .equ    ARGCMASK, 0xff000000

        .text
        .globl  _start
_start:
        /* Use %eax as an intermediate register to push envp (== &envp[0]),
           argv (== &argv[0]), and argc, one by one onto stack (saving and
           restoring %eax around).  Then call mainprog and, if it returns,
           syscall exit.  (Avoiding leal, which we haven't covered.)
        */
        movl    %esp, %ebp         /* First stack frame --- no caller! */
        movl    %eax,-16(%ebp)     /* Save %eax, sufficiently high on stack */
        movl    (%ebp), %eax       /* Get argc */
        testl    $ARGCMASK, %eax   /* Check if it is too big */
        jnz        err_exit        /* If so, abort */

        shll    $2, %eax           /* %eax now = 4*argc */
        addl    %ebp, %eax         /* %eax now = &argv[argc-1] */
        addl    $8, %eax           /* %eax now = &envp[0] */
        pushl    %eax              /* Push &envp[0] onto stack */

        movl    %ebp,%eax          /* %eax now = &argv[0] - 4 */
        addl    $4,%eax            /* %eax now = &argv[0] */
        pushl    %eax              /* Push &argv[0] onto stack */

        movl    (%ebp), %eax       /* Get argc again */
        pushl    %eax              /* Push argc onto stack */

        movl    -16(%ebp), %eax    /* Restore %eax */
        call    mainprog           /* Call main C prog */

        /* Main C program returned, we now have to do the exit */
        movl    %eax, %ebx         /* Put return code in %ebx */
        jmp     exitpoint          /* And exit! */

err_exit:
        /* Too large argc value, abort with exit code 128 */
        movl    $128, %ebx

exitpoint:                         /* Exit syscall, use code found in %ebx */
        movl    $1, %eax
        int        $0x80
        jmp        exitpoint       /* Nowhere to return, I am the startup! */

