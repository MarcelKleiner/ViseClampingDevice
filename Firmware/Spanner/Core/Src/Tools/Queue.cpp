/*
 * Queue.cpp
 *
 *  Created on: Nov 5, 2022
 *      Author: marcel
 */

#include "Queue.h"

/*
 * @brief enqueue data to Buffer,
 * 		  if the buffer is full, the old datas will be overwritten
 *
 * @param data to push in queue
 * @return none
 */
void Queue::Enqueue(uint8_t data)
{
	//push data to buffer
	buffer[enqueuePointer] = data;

	if (dequeuePointer == 0 && enqueuePointer == BUFFER_SIZE - 1)
	{
		dequeuePointer++;
		enqueuePointer = 0;
	}
	else if (dequeuePointer == BUFFER_SIZE - 1
			&& enqueuePointer == dequeuePointer - 1)
	{
		dequeuePointer = 0;
		enqueuePointer++;
	}
	else if (enqueuePointer + 1 == dequeuePointer)
	{
		dequeuePointer++;
		enqueuePointer++;
	}
	else if (enqueuePointer == BUFFER_SIZE - 1)
	{
		enqueuePointer = 0;
	}
	else
	{
		enqueuePointer++;
	}
}

/*
 * @brief dequeue data from buffer if buffer is not empty
 *
 * @param none
 * @return data at actual dequeue position
 */
uint8_t Queue::Dequeue()
{
	//return 0 if queue is empty
	if (IsEmpty())
	{
		return 0;
	}
	//get acutal dequeue pointer
	uint8_t dequeuePointerTemp = dequeuePointer;

	//incfement dequeuePointer, set to 0 if queue overflow occures
	if (dequeuePointer == BUFFER_SIZE - 1)
	{
		dequeuePointer = 0;
	}
	else
	{
		dequeuePointer++;
	}
	//return queue data
	return buffer[dequeuePointerTemp];
}

/*
 * @brief check if queue is empty
 *
 * @param none
 * @return true if queue is empty otherwise false
 */
bool Queue::IsEmpty()
{
	return (enqueuePointer == dequeuePointer);
}

/*
 * @brief reset Buffer
 *
 * @param none
 * @return none
 */
void Queue::Reset()
{
	enqueuePointer = 0;
	dequeuePointer = 0;
}
