/*
  File: startup32-jmp.S

  Purpose:  Pass startup argc/argv/envp values to main C code
  via external variables without disturbing the stack.

  It is assumed that externally three special C global variables
  in data memory have been allocated by the main C code, namely:
 
    int my_argc;
    char **my_argv, **my_envp;

  This 32bit assembly code acts as startup code to be run before
  the main C code, for the purpose of initializing the above
  three variables, and leaving the stack in its startup state.
  It takes the argc, argv, envp values found on the stack at
  program startup (set up at start-of-execetion by the kernel
  under the execve system call), and copies them to the above
  three special C global variables in data memory.

  This assembly program flows as follows:

    - Execution begins at entry point _start, sanity checks argc value
    - Initializes my_argc (int), my_argv and my_envp (ptrs) by using
      correct stack values and locations
    - Jumps to mainprog (the C program's main function), never returns!
  
  The exectuable C program can then access the arguments (my_argv)
  and the environment (my_envp) on stack through these variables
  without having to deal with assembly, while having essentially
  the exact same stack state that was set by kernel.

  Since the purpose of this code is to preserve the stack/stack-ptr,
  we cannot spawn the main C program using the call instruction.
  This means the main C program has to ensure its own exit.

*/ 
        .globl   my_argc
        .globl   my_argv
        .globl   my_envp
        /*
          We will just initialize these external variables here
          (not allocate storage).  Storage for these three 32bit 
          values must be allocated in the C code for mainprog().
        */

        .globl  mainprog        /* Name of C function that we will jump to */

        /* Use a sane max value for argc */
        .equ    ARGCMASK, 0xffff0000    /* max argc 0xffff = 65535  */

        .text
        .globl  _start
_start:
        pushl   %eax            /* Save %eax on top of stack */
        popl    %eax            /* Set %esp back to original location */
        popl    %eax            /* Get argc value from stack into %eax */
        /* Stack ptr now points to start of argv array (%esp == &argv[0]),
           and %eax holds the 32-bit argc integer */

        movl    %esp, my_argv   /* Save stack ptr == &argv[0] in C variable */
        movl    %eax, my_argc   /* Save the argc value in memory (of C prog) */
        testl   $ARGCMASK, %eax /* Check if argc is too big */
        jnz     err_exit        /* If so, abort */

        /* 
           It remains to compute start add of envp array, i.e. &envp[0].
           The null ptr terminating argv is at addr &argv[0] + 4*argc,
           so envp[0] is at addr &argv[0] + 4*argc + 4.  Since the stack ptr
           is now %esp == &argv[0], we can make %eax point to envp[0]
           (i.e. %eax == &envp[0]), by setting %eax := %esp + 4*%eax + 4.
        */
        shll    $2, %eax        /* Shift left 2 bits == multiply argc by 4 */
        addl    %esp, %eax      /* %eax now points to null ptr at end of argv */
        addl    $4, %eax        /* %eax now points to envp[0] */
        /* Or, we could have simply done leal 4(%esp,%eax,4),%eax instead */

        movl    %eax, my_envp   /* Save addr of envp[0] in ext C var my_envp */

        /* Done initializing the three external C variables */

        subl    $8, %esp        /* Move %esp above %eax val stored in stack */
        popl    %eax            /* Restore %eax from stored val, restore %esp */
        /* Stack now in original state! */

        jmp     mainprog        /* Not call, to avoid disturbing the stack! */

err_exit:
        /* Too large argc, abort with exit code 128 */
        movl    $1, %eax
        movl    $128, %ebx
        int     $0x80
        jmp     err_exit        /* Nowhere to return to, I am the startup */

