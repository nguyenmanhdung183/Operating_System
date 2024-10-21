#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

struct SharedData {
    int x, y, z;
    int ready;
};

int main() {
    // Tạo khóa cho vùng nhớ dùng chung
    key_t key = ftok("shmfile", 65);
    
    // Tạo vùng nhớ dùng chung
    //shmget(key_t key, size_t size, int shmflg)
    int shmid = shmget(key, sizeof(struct SharedData), 0666 | IPC_CREAT);// tạo phân đoạn bộ nhớ mới
    //void * shmat(int shmid, const void *shmaddr, int shmflg)
    ////trả về địa chỉ mà phân đoạn bộ nhớ chia sẻ được gắn
    struct SharedData* data = shmat(shmid, NULL, 0);
    data->ready = 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("ERROR");
        return 1;
    }

    if (pid == 0) {
        // Process con
        while (data->ready != 1);
        data->z = data->x + data->y;
        data->ready = 0;
        // Kết thúc process con
        exit(0);
    } else {
        // Process mẹ
        printf("Nhập x: ");
        scanf("%d", &data->x);
        printf("Nhập y: ");
        scanf("%d", &data->y);
        data->ready = 1;
        while (data->ready != 0);

        printf("x + y =  %d\n", data->z);

        // Giải phóng vùng nhớ dùng chung
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);

        return 0;
    }
}
