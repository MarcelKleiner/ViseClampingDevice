/*
 * Error.h
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#ifndef SRC_ERROR_ERROR_H_
#define SRC_ERROR_ERROR_H_

class Error{

public:

	enum EERROR_CODE{
		NO_ERROR = 0x00,
		OVER_CURRENT_ERROR = 0x01,
		UNDERVOLTAGE_ERROR = 0x02,
		OVER_POS_ERROR = 0x03,
		UNDER_POS_ERROR = 0x04,
		COM_ERROR = 0x05,
	};



	void setError(EERROR_CODE error);
	void resetError();
	EERROR_CODE getError();

	void error2LED();




private:

	EERROR_CODE errorCode;



};




#endif /* SRC_ERROR_ERROR_H_ */
