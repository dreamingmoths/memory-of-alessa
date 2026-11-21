#include "taskman/shtskman.h"

int shTskTaskMax      = 0;
int shTskTaskEmptyNum = 0;
shTskTASK* shTskTaskEmptyTop = NULL;
shTskTASK* shTskTaskListTop[TASK_LIST_SIZE];





























void shTSKInitTaskList(u_char* buffer, u_int size) {
    shTskTASK* ptr;
    int* cptr;
    int i;

    shTskTaskMax = size / sizeof(shTskTASK);


    cptr = buffer;
    for (i = shTskTaskMax * sizeof(shTskTASK) / 4 - 1; i >= 0; i--)
        *cptr++ = 0;

    for (i = 0; i < TASK_LIST_SIZE; i++) {

        shTskTaskListTop[i] = buffer + i * sizeof(shTskTASK);
        shTskTaskListTop[i]->exe.next = shTskTaskListTop[i];
        shTskTaskListTop[i]->exe.prev = shTskTaskListTop[i];
    }

    ptr = buffer + sizeof(shTskTASK) * TASK_LIST_SIZE;
    shTskTaskEmptyTop = ptr;
    for (i = TASK_LIST_SIZE; i < shTskTaskMax - 1; i++, ptr++) {

        ptr->exe.next = ptr + 1;
        ptr->exe.atr = 0;
    }
    ptr->exe.next = NULL;
    ptr->exe.atr = 0;

    shTskTaskEmptyNum = shTskTaskMax - TASK_LIST_SIZE;
}


















shTskTASK* shTSKSetTask(void (* func)(void *), u_char num) {
    return shTSKSetTaskPrev(shTskTaskListTop[num], func);
}



































































shTskTASK* shTSKSetTaskPrev(shTskTASK* task, void (* func)(void *)) {
    shTskTASK* a;
    shTskTASK* b;

    if (shTskTaskEmptyNum != 0) {

        a = shTskTaskEmptyTop;
        b = task->exe.prev;
        shTskTaskEmptyTop = a->exe.next;
        shTskTaskEmptyNum--;
        a->exe.prev = b;
        a->exe.next = task;
        a->exe.adrs = func;
        a->exe.mode = 0;
        a->exe.atr  = 0;
        task->exe.prev = a;
        b->exe.next = a;
        return a;
    }
    return NULL;

}
















void shTSKDelTask(shTskTASK* task) {
    task->exe.adrs = NULL;
}





















shTskTASK* shTSKCutTask(shTskTASK* task) {
    shTskTASK* a;
    shTskTASK* b;

    a = task->exe.prev;
    b = task->exe.next;
    a->exe.next = b;
    b->exe.prev = a;
    task->exe.adrs = NULL;
    task->exe.next = shTskTaskEmptyTop;
    shTskTaskEmptyTop = task;
    shTskTaskEmptyNum++;
    return b;

}
















void shTSKExecuteTask(u_char num) {
    shTskTASK* ptr;

    ptr = shTskTaskListTop[num]->exe.next;

    while(ptr != shTskTaskListTop[num]) {

        if (ptr->exe.adrs == NULL)
            ptr = shTSKCutTask(ptr);
        else {

            ptr->exe.adrs(ptr);
            ptr = ptr->exe.next;
        }
    }
}

















































































































shTskTASK* shTSKSearchTaskWithAtr(int atr, shTskTASK* start, u_char num) {
    shTskTASK* ptr;

    ptr = start;
    while(ptr != shTskTaskListTop[num]) {

        if (ptr->exe.atr == atr)
            return ptr;
        ptr = ptr->exe.next;
    }
    return NULL;
}














































void shTSKFreeTaskLine(u_char num) {
    shTskTASK* ptr;

    ptr = shTskTaskListTop[num]->exe.next;
    while(ptr != shTskTaskListTop[num])
        ptr = shTSKCutTask(ptr);
}

