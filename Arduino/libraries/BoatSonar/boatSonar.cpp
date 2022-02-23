/** ***************************************************************************
 * @file
 *
 * @brief   boatSonar class function definitions
 *****************************************************************************/
#include "boatSonar.h"



 /** ***************************************************************************
  * @author Kyle Houchin
  *
  * @par Description:
  * This function will pinMode pins (2,3,18,19) to be used for zones.
  * They will be setup simmular to attachInterupt(pin #, CHANGE);
  * where the ISR( INT#_vect ) is the function that is called when 
  * the pin changes states. 
  *
  *****************************************************************************/
BoatSonar::BoatSonar() {
    setInterupts();
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function will take two bounds and save then to the class
 * it will then enable bound checking. will retrun -1 for invlaid disstances 
 * in the getDistance( long distance[], int size, boatZone bz ), disstance 
 * array. At the location of the sonar that had an invalid reading
 * 
 * @todo need to implement into data retrun
 *
 * @param[in] lower_bound - lower cutoff value in cm for sonar
 * @param[in] upper_bound - cutoff value in cm for sonar
 * 
 * @returns true succesfull
 * @returns false if bounds are invalid
 *
 *****************************************************************************/
bool BoatSonar::setBound( int lower_bound, int upper_bound )
{
    if (lower_bound < 0)
        return false;
    if (lower_bound > upper_bound)
        return false;

    bound_enable = true;
    lowerBound = lower_bound;
    upperBound = upper_bound;
    return true;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function will trun on or off bound checking on the getDistance() function.
 * Dont need to use if setBound() was called.
 * 
 * Default values are:
 * int lowerBound = 2;        //close cut off distance in cm from sensor
 * int upperBound = 60;
 *
 * @param[in] value - true for inabled, false to dissable
 *
 *****************************************************************************/
void BoatSonar::useBound( bool value )
{
    bound_enable = value;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function sets up a zone. If this function is not called on a zone it will
 * defualt to dissabled and will not return anything on the getDistance() call.
 * If this function is called twice on the same zone the old setup will be 
 * discarded and this call will be implemeted. If the inputs are invalid it will 
 * return false and leave the zone disabled.
 *
 * @param[in] bz - selecting the zone, BoatSonar::<MID,STAR,PORT,BACK>
 * @param[in] triggerPin[] - a array that has the trigger pins # in it.
 * @param[in] numtriggerPins - this is how many items is in the triggers array
 *
 *****************************************************************************/
bool BoatSonar::initZone( boatZone bz, int triggerPin[], int numtriggerPins )
{
    //SONAR_LIMIT = 5 <Default
    if (numtriggerPins > SONAR_LIMIT)
        return false;

    //checks if zone is allready setup
    if (Zones[bz] != nullptr)
    {
        //if so it deletes the old one. (advoids memory leaks )
        delete Zones[bz];
        Zones[bz] = nullptr;
    }
    //allocated a new instance of a zone.
    Zones[bz] = new zone( bz, triggerPin, numtriggerPins ); //mid is 0
    if (Zones[bz] == nullptr) //allocation failed
    {
        //error
        return false;
    }
    //returns true if everything is succesfull
    return true;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function retrieves the data from a zone. Each index is rellated to a
 * trigger pin. In the order of the triggerPin[] array from the initZone() function.
 * 
 * If the zone is not initialized yet or failed it this function will retrun false.
 * If bounding is enabled, invalid distances will return as -1. (over or under 
 * Bounds). Nothing is changed if the dounding is dissabled (this is Default).
 *
 * @param[in] distance[] - long datatype: each index is rellated to a trigger pin. 
 * @param[in] size - a array that has the size of distance.
 * @param[in] bz - selecting the zone, BoatSonar::<MID,STAR,PORT,BACK>
 *
 * @returns true if valid data is sotored
 * 
 *****************************************************************************/
bool BoatSonar::getDistance( long distance[], int size, boatZone bz )
{
    return Zones[bz]->getData( distance, size );
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function is the most important. It handles the collection proccess on all
 * the zones. Call it once a cycle and give 1000ms after the function returns
 * before data collection using getDistance(). 
 * 
 * This function will loop though all 4 zones check if there enabled. If so it 
 * will pulse Trigger pin and collect the data from the echo. This is simi-multi-
 * Threaded. It is faster than individualy reading each sensor at a time. It
 * also does not use pulseIn(). So the delay from that function is not used and
 * it will collect the data during the delayMicroseconds( 1000 ); meaning it cuts
 * time off that part too.
 *
 *****************************************************************************/
void BoatSonar::updateBoatSonar()
{
    int i,j;
    int sizes[4] = { 0 };
    bool flag = false;
    //get the sizes
    for (i = 0; i < 4; i++)
    {   
        //checks if the zone is inabled 
        if (Zones[i] != nullptr)
        {
            //this gets the number of trigger pins in the zone
            sizes[i] = Zones[i]->getSize();
        }
        else
        {
            //used below to pass loop
            sizes[i] = 0;
        }
    }

    //loops for maximum size.
    for (j = 0; j < SONAR_LIMIT; j++)
    {
        //loops for # of zones
        for (i = 0; i < 4; i++)
        {
            //if size of the zone is 0 or it has reached the 
            //number of pins in the zone, it will pass
            if (sizes[i] != 0)
            {
                if (!(sizes[i]-1) > j)
                {
                    //update zone, calls one trigger at a time.
                    Zones[i]->updatezone();
                    //Serial.println(micros());
                    
                    flag = true;
                    //this makes sure to off set the collection so 
                    //multipule pin interupts are advodied
                    delayMicroseconds(5);
                }
            }
        }
        //flag is if a zone had been updated
        if (flag)
            //makes sure all noze on echo pin is cleared
            delayMicroseconds( 1000 );
        flag = false;
    }
}
