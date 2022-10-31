#include <stdio.h>
#include<stdlib.h>

typedef struct {
    int ID;
    int time;
} Task;

int IndexOfMin(int *Array, int Number) {
    int i;
    int index = 0;
    int min = Array[0];
    for (i = 1; i < Number; i++) {
        if (Array[i] < min) {
            index = i;
            min = Array[i];
        }
    }
    return index;
}

int *MultiMachineSchedule(Task *Tasks, int Task_number, int Machine_number) {
    int *Finish_times = (int *) malloc(sizeof(int) * Machine_number);
    int *Task_lists = (int *) malloc(sizeof(int) * Machine_number);
    int i;

    for (i = 0; i < Machine_number; i++) {
        Finish_times[i] = 0;
        Task_lists[i] = 0;
    }
    for (i = 0; i < Machine_number; i++) {
        Task_lists[i] = Task_lists[i] * 10 + Tasks[i].ID;
        Finish_times[i] += Tasks[i].time;
    }
    for (; i < Task_number; i++) {
        int index = IndexOfMin(Finish_times, Machine_number);
        Task_lists[index] = Task_lists[index] * 10 + Tasks[i].ID;
        Finish_times[index] += Tasks[i].time;
    }
    return Task_lists;
}

int main() {
    const int Task_number = 7;
    Task tasks[Task_number] = {{1, 2},
                               {2, 14},
                               {3, 4},
                               {4, 16},
                               {5, 6},
                               {6, 5},
                               {7, 3},
    };
    int Machine_number = 3;
    int *task_lists = MultiMachineSchedule(tasks, Task_number, Machine_number);
    for (int i = 0; i < Machine_number; i++) {
        printf("%d\n", task_lists[i]);
    }
    return 0;
}
