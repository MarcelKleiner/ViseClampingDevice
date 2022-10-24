/*
 * Error.h
 *
 *  Created on: 22.10.2022
 *      Author: marce
 */

#ifndef SRC_ERROR_ERROR_H_
#define SRC_ERROR_ERROR_H_


class Error{
public:
	void FatalError();
	void Error();


	enum FATAL_ERRROR{
		RFM_COM_F_ERROR,

	};

	enum ERROR{

	};


private:

	uint8_t errorCode;


};




#endif /* SRC_ERROR_ERROR_H_ */
