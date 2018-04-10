

typedef struct
{
    uint8_t data[78];
} queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
} queue_struct_t;

queue_struct_t s_queueList;

void queue_init(void)
{
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}

bool queue_isFull(void)
{
    bool retVal = false;
    if (MAX_QUEUE_SIZE == size)
    {
        retVal = true;
    }
    return retVal;
}

bool queue_isEmpty(void)
{
    bool retVal = false;
    if (0 == s_queuList.size)
    {
        retVal = true;
    }
    return retVal;
    
}

uint8_t *putPtr == NULL;

void UART_ISR(void)
{
    putPtr(index) = ch;
    index++;
    if ('\n' == ch)
    {
        index = 0;
        queue_Put();
        queue_getUnuseElement(uint8_t **) &putPtr);
    }
    
}

bool queue_getUnuseElement(uint8_t **outBuff)
{
    uint8_t putIndex = s_quequeList.putIndex % MAX_QUEUE_SIZE;

    if (!queue_isFull())
    {
        *outBuff = (uint8_t *) &s_queueList.element[putIndex];
    }
}

void queue_put(void)
{
    s_queueList.putIndex++;
    s_queueList.size++;
}
void queue_getData(uint8_t **outBuff)
{
    uint8_t getIndex = s_quequeList.getIndex % MAX_QUEUE_SIZE;
    if (!queue_isFull())
    {
        *outBuff = (uint8_t *) &s_queueList.element[getIndex];
    }
}


void queue_get(void)
{
    s_queueList.getIndex++;
    s_queueList.size--;
}

uint8_t *getPtr;

main()
{
    while (1)
    {
        if (!queue_isEmpty())
        {
            queue_getData(uint8_t **)&getPtr);
            status = parse(getPtr,&outData);
            if () printf
        }
    }
}
