#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>

void do_command(char** argv) {
    auto start = std::chrono::steady_clock::now();

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return;
    }

    if (pid == 0) {
        execvp(argv[0], argv);
        std::cerr << "Exec failed" << std::endl;
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        if (WIFEXITED(status)) {
            std::cout << "Command completed with " << WEXITSTATUS(status) << " exit code and took " << duration << " seconds." << std::endl;
        } else {
            std::cerr << "Command did not terminate normally" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
        return 1;
    }

    do_command(argv + 1);

    return 0;
}
