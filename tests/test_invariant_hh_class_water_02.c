#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* We'll test the actual function by compiling and running it in a subprocess */
static void run_function_with_input(const char *input) {
    int pipefd[2];
    pid_t pid;
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        /* Child process: compile and run the actual source file */
        close(pipefd[0]);
        
        /* Write the test input to the pipe */
        write(pipefd[1], input, strlen(input));
        close(pipefd[1]);
        
        /* Reopen stdin from the pipe */
        dup2(pipefd[1], STDIN_FILENO);
        
        /* Compile and run the actual source */
        execlp("sh", "sh", "-c", 
               "cd silent-hill-2/src/Effect2 && "
               "gcc -o test_prog hh_class_water_02.c -DMAIN 2>/dev/null && "
               "./test_prog <&0", 
               NULL);
        
        /* If we get here, exec failed */
        perror("exec");
        exit(EXIT_FAILURE);
    } else {
        /* Parent process: wait for child */
        close(pipefd[0]);
        close(pipefd[1]);
        
        int status;
        waitpid(pid, &status, 0);
        
        /* The invariant: child should not crash (no segmentation fault) */
        ck_assert_msg(!WIFSIGNALED(status) || WTERMSIG(status) != SIGSEGV,
                     "Buffer overflow detected with input: %s", input);
    }
}

START_TEST(test_buffer_reads_within_bounds)
{
    /* Invariant: Buffer reads never exceed the declared length */
    const char *payloads[] = {
        "A",                          /* Valid input (boundary minimum) */
        "1234567890",                 /* Normal valid input */
        "A".repeat(1024),             /* Exact exploit case - oversized 2x */
        "X".repeat(5120),             /* Boundary: 10x normal size */
        "\x00\x01\x02" "A".repeat(1000) /* Mixed binary data */
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);
    
    for (int i = 0; i < num_payloads; i++) {
        run_function_with_input(payloads[i]);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;
    
    s = suite_create("Security");
    tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_buffer_reads_within_bounds);
    suite_add_tcase(s, tc_core);
    
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s = security_suite();
    sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}