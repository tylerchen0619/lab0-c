#ifndef LAB0_CONSOLE_H
#define LAB0_CONSOLE_H

/* Implementation of simple command-line interface */

/* Each command defined in terms of a function */
typedef bool (*cmd_function)(int argc, char *argv[]);

/* Information about each command */
/* Organized as linked list in alphabetical order */
typedef struct CELE cmd_ele, *cmd_ptr;
struct CELE {
    char *name;
    cmd_function operation;
    char *documentation;
    cmd_ptr next;
};

/* Optionally supply function that gets invoked when parameter changes */
typedef void (*setter_function)(int oldval);

/* Integer-valued parameters */
typedef struct PELE param_ele, *param_ptr;
struct PELE {
    char *name;
    int *valp;
    char *documentation;
    /* Function that gets called whenever parameter changes */
    setter_function setter;
    param_ptr next;
};

/* Initialize interpreter */
void init_cmd();

/* Add a new command */
void add_cmd(char *name, cmd_function operation, char *documentation);

/* Add a new parameter */
void add_param(char *name,
               int *valp,
               char *doccumentation,
               setter_function setter);

/* Execute a sequence of commands read from a file */
bool interpret_file(FILE *fp);

/* Extract integer from text and store at loc */
bool get_int(char *vname, int *loc);

/* Add function to be executed as part of program exit */
void add_quit_helper(cmd_function qf);

/* Turn echoing on/off */
void set_echo(bool on);

/* Is it time to quit the command loop? */
bool cmd_done();

/* Complete command interpretation */
/* Return true if no errors occurred */
bool finish_cmd();

/*
 * Handle command processing in program that uses select as main
 * control loop.
 */
int cmd_select(int nfds,
               fd_set *readfds,
               fd_set *writefds,
               fd_set *exceptfds,
               struct timeval *timeout);

/* Run command loop.  Non-null infile_name implies read commands from that file
 */
bool run_console(char *infile_name);

#endif /* LAB0_CONSOLE_H */
