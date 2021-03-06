#include "prompt.h"

char **func_names;

static char *line = (char *) NULL;

static char **function_name_completion (const char *, int, int);
static char *function_name_generator (const char *, int);

void prompt_init (char **names) {
    func_names = names;
}

char *type_prompt (char *command) {
    rl_attempted_completion_function = function_name_completion;

    if (command) free (command);
    line = readline ("> ");
    if (line) {
        add_history (line);
        command = strndup (line, strcspn (line, " "));
        free (line);
        return command;
    }
    return command = strdup ("");
}

char *type_file (char *file) {
    rl_attempted_completion_function = NULL;

    if (file) free (file);
    line = readline ("");
    if (line) {
        add_history (line);
        file = strndup (line, strcspn (line, " "));
        free (line);
        return file;
    }
    return file = strdup ("");
}

char ** function_name_completion (const char *text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches (text, function_name_generator);
}

char * function_name_generator (const char *text, int state) {
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen (text);
    }

    while ((name = func_names[list_index++])) {
        if (strncmp (name, text, len) == 0) {
            return strdup (name);
        }
    }

    return NULL;
}
