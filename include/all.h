#define _GNU_SOURCE

void unit_time(void);
void set_priority(pid_t pid, int priority);
void set_cpu(pid_t pid, int n);
void fork_process(pid_t* pid, char* N, int T);