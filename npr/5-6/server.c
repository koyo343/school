#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd[2];
    pid_t pid, pwait;
    int status;
    pipe(fd); // 要素数2の整数配列を引数にpipe()実行
    pid = fork();

    if(pid == 0){ // 子プロセス ls -l の実行
        close(fd[0]); close(1); // 不要記述子の削除
        close(1); // 標準出力の削除
        dup(fd[1]); close(fd[1]); // パイプ出力のリダイレクト
        execl("/bin/ls","ls","-l", NULL);
    }
    else{ // 親プロセス grep put の実行
        pwait = wait(&status);
        printf("child %d is finished¥n", pwait);
        close(fd[1]); close(0); // 不要記述子の削除
        dup(fd[0]); close(fd[0]); // パイプ入力のリダイレクト
        execl("/bin/grep","grep", "put", NULL);
    }
}
