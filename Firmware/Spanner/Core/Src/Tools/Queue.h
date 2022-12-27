/*
 * Queue.h
 *
 *  Created on: Nov 5, 2022
 *      Author: marce
 */

#ifndef SRC_TOOLS_QUEUE_H_
#define SRC_TOOLS_QUEUE_H_

#include "stdint.h"

#define BUFFER_SIZE 10

class Queue{

public:
	void Enqueue(uint8_t data);
	uint8_t Dequeue();
	bool IsEmpty();
	void Reset();
private:
	uint8_t enqueuePointer = 0;
	uint8_t dequeuePointer = 0;

	uint8_t buffer[BUFFER_SIZE];
};

#endif /* SRC_TOOLS_QUEUE_H_ */
