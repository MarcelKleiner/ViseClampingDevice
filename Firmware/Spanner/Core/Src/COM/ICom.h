/*
 * ICom.h
 *
 *  Created on: 25.12.2022
 *      Author: marce
 */

#ifndef SRC_COM_ICOM_H_
#define SRC_COM_ICOM_H_

#include "stddef.h"

class ICom{

	public:
		virtual bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) = 0;
		virtual bool Receive(uint8_t *data = NULL, uint8_t length = 0) = 0;

};



#endif /* SRC_COM_ICOM_H_ */
