/** ***************************************************************************
 * @file
 *
 * @brief  setup for pin interupts for echo pins
 *****************************************************************************/
#ifndef INTERUPTS_H
#define INTERUPTS_H

#include "arduino.h"

//this fuction fully handles setting up the intrupt pins
void setInterupts();
void zone3Setup();
void zone2Setup();
void zone1Setup();
void zone0Setup();

long getZone( int zone );

#endif // !INTERUPTS_H
