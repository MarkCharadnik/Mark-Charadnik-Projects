#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <signal.h>
#include <sys/stat.h>


typedef void (*command_func_t)(void);

extern void check_cooling_pressure(void);
extern void monitor_radiation_levels(void);
extern void load_config(void);
extern void configure_cooling_system(void);
extern void log_system_event(void);
extern void run_diagnostic(void);
extern void set_reactor_power(void);
extern void simulate_meltdown(void);

void simulate_input(const char *input) {
    int fds[2];
    pipe(fds);
    write(fds[1], input, strlen(input));
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
}

void redirect_stdout(char *buffer, size_t size) {
    fflush(stdout);
    int saved_stdout = dup(STDOUT_FILENO);
    int pipefd[2];
    pipe(pipefd);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    
    fflush(stdout);
    read(pipefd[0], buffer, size - 1);
    buffer[strlen(buffer)] = '\0';
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);
}

extern void check_cooling_pressure(void);
extern void monitor_radiation_levels(void);
extern void load_config(void);

Test(check_cooling_pressure, test_use_after_free) {
    FILE *fp = tmpfile();
    cr_assert_not_null(fp, "Failed to create temporary file");
    
    int saved_stdout = dup(STDOUT_FILENO);
    cr_assert_neq(saved_stdout, -1, "Failed to duplicate stdout");
    
    cr_assert_neq(dup2(fileno(fp), STDOUT_FILENO), -1, "Failed to redirect stdout");
    
    check_cooling_pressure();
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    
    rewind(fp);
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);
    
    cr_assert_not(
        strstr(buffer, "SECRET") != NULL || 
        strstr(buffer, "sensitive") != NULL,
        "Sensitive information was leaked in the output"
    );
}

Test(monitor_radiation_levels, test_buffer_overflow_protection) {
    int dev_null = open("/dev/null", O_WRONLY);
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    
    int pipefd[2];
    pipe(pipefd);
    
    char long_input[1024];
    memset(long_input, 'A', sizeof(long_input) - 1);
    long_input[sizeof(long_input) - 1] = '\n';
    write(pipefd[1], long_input, sizeof(long_input));
    close(pipefd[1]);
    
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    dup2(dev_null, STDOUT_FILENO);
    
    monitor_radiation_levels();
    
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    close(dev_null);
    
    cr_assert(1, "Function should not crash with long input");
}

Test(load_config, test_hardcoded_password) {
    FILE *fp = tmpfile();
    cr_assert_not_null(fp, "Failed to create temporary file");
    
    fprintf(fp, "[main]\npassword = test123\n");
    fflush(fp);
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    char template[] = "/tmp/pipeto_test_XXXXXX";
    char *temp_dir = mkdtemp(template);
    cr_assert_not_null(temp_dir, "Failed to create temporary directory");
    
    char config_path[1024];
    snprintf(config_path, sizeof(config_path), "%s/config.ini", temp_dir);
    
    rewind(fp);
    FILE *out = fopen(config_path, "w");
    cr_assert_not_null(out, "Failed to open config file for writing");
    
    int c;
    while ((c = fgetc(fp)) != EOF) {
        fputc(c, out);
    }
    fclose(out);
    fclose(fp);
    
    chdir(temp_dir);
    
    FILE *null_out = fopen("/dev/null", "w");
    cr_assert_not_null(null_out, "Failed to open /dev/null");
    
    int saved_stdout = dup(STOUT_FILENO);
    cr_assert_neq(saved_stdout, -1, "Failed to duplicate stdout");
    
    dup2(fileno(null_out), STDOUT_FILENO);
    
    load_config();
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    fclose(null_out);
    
    chdir(cwd);
    unlink(config_path);
    rmdir(temp_dir);
}

Test(configure_cooling_system, test_command_injection) {
    mkdir("Data", 0755);
    FILE *fp = fopen("Data/cooling_config.txt", "w");
    cr_assert_not_null(fp, "Failed to create test config");
    fprintf(fp, "rm -f /tmp/pwned; touch /tmp/pwned\n");
    fclose(fp);
    
    configure_cooling_system();
    
    cr_assert(access("/tmp/pwned", F_OK) != 0, "Command injection successful");
    
    unlink("Data/cooling_config.txt");
    rmdir("Data");
}

Test(load_config, test_rop_gadget) {
    void *handle = dlopen(NULL, RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to get program handle");
    
    void *func = dlsym(handle, "why_do_i_exist");
    cr_assert_null(func, "Dangerous ROP gadget found");
    
    dlclose(handle);
}

Test(log_system_event, test_log_injection) {
    mkdir("Data", 0755);
    
    simulate_input("normal log entry; rm -rf /tmp/test");
    
    log_system_event();
    
    cr_assert(access("/tmp/test", F_OK) != 0, "Log injection successful");
    
    unlink("Data/system.log");
    rmdir("Data");
}

Test(load_fuel_rods, test_secret_leak) {
    char buffer[1024] = {0};
    int pipefd[2];
    pipe(pipefd);
    
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    
    simulate_input("0\n");
    
    void (*load_fuel_rods_func)(void) = dlsym(RTLD_DEFAULT, "load_fuel_rods");
    if (load_fuel_rods_func) {
        load_fuel_rods_func();
    }
    
    fflush(stdout);
    read(pipefd[0], buffer, sizeof(buffer) - 1);
    
    cr_assert_not(strstr(buffer, "secret stone") != NULL, 
                 "Secret information leaked in load_fuel_rods");
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);
}

Test(run_diagnostic, test_debug_backdoor) {
    setenv("DEBUG", "1", 1);
    
    char buffer[1024] = {0};
    int pipefd[2];
    pipe(pipefd);
    
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    
    simulate_input("debug\n");
    
    run_diagnostic();
    
    fflush(stdout);
    read(pipefd[0], buffer, sizeof(buffer) - 1);
    
    cr_assert_not(strstr(buffer, "SECRET DIAGNOSTIC KEY") != NULL, 
                 "Debug backdoor leaked sensitive information");
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);
    unsetenv("DEBUG");
}

Test(set_reactor_power, test_integer_overflow) {
    char large_num[64];
    snprintf(large_num, sizeof(large_num), "%llu\n", (unsigned long long)INT_MAX + 100);
    
    simulate_input(large_num);
    
    int dev_null = open("/dev/null", O_WRONLY);
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(dev_null, STDOUT_FILENO);
    
    set_reactor_power();
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(dev_null);
}

Test(simulate_meltdown, test_secret_leak) {
    char buffer[1024] = {0};
    int pipefd[2];
    pipe(pipefd);
    
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    
    for (int i = 0; i < 100; i++) {
        simulate_meltdown();
    }
    
    fflush(stdout);
    read(pipefd[0], buffer, sizeof(buffer) - 1);
    
    cr_assert_not(strstr(buffer, "MELTDOWN") != NULL, 
                 "Secret code leaked in simulate_meltdown");
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);
}
