/*
 * relay.h
 *
 *  Created on: Apr 11, 2022
 *      Author: handddle
 */

#include "main.h"

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

/*	@fn 	void set_relay_on(bool command);
 * 	@brief 	Function used to activate or deactivate the relay
 * 	@param 	command is the variable used as parameter : true closed the relay because is a normally opened relay
 */
void set_relay_on(bool command);

#endif /* INC_RELAY_H_ */
