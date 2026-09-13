#include "queue.h"

void queue_init(Queue *queue)
{
    if (queue != 0)
    {
        queue->front = 0;
        queue->rear = 0;
        queue->size = 0;
    }
}

int queue_enqueue(Queue *queue, Position value)
{
    if (queue == 0)
    {
        return 0;
    }

    if (queue->size >= QUEUE_CAPACITY)
    {
        return 0;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->size++;

    return 1;
}

int queue_dequeue(Queue *queue, Position *value)
{
    if (queue == 0 || value == 0)
    {
        return 0;
    }

    if (queue->size <= 0)
    {
        return 0;
    }

    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    queue->size--;

    return 1;
}

int queue_is_empty(const Queue *queue)
{
    return queue == 0 || queue->size == 0;
}
