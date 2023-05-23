#include "loopqueue.h"

int main()
{
    loopqueue_t *q = create_empty_loopqueue();
    insert_data_queue(q, 10);
    return 0;
}