/*
* Copyright (c) 2016, Wind River Systems, Inc.
*
* Redistribution and use in source and binary forms, with or without modification, are
* permitted provided that the following conditions are met:
*
* 1) Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2) Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* 3) Neither the name of Wind River Systems nor the names of its contributors may be
* used to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*
 * DESCRIPTION
 *  calendar.c - implements general calendar functions
 *
 */


#include "strutils.h"

/*
 *  Local Defines
 */
#define TWELVE_MONTHS    12          /* General Defines */
#define STRING_MATCH      0
#define LEGITIMATE_DAYNUM 0
#define INITIALIZED       0x1234

/*
 *  Global Definitions
 */

struct  month{                       /* Array of 'month' structs  */
                char  *monthName;    /* (the values are for 1997) */
                short  numOfDays;
                char  *startDay;
              } MONTH[] = {
                            {"January",  31, "Wednesday"},
                            {"February", 28, "Saturday" },
                            {"March",    31, "Saturday" },
                            {"April",    30, "Tuesday"  },
                            {"May",      31, "Thursday" },
                            {"June",     30, "Sunday"   },
                            {"July",     31, "Tuesday"  },
                            {"August",   31, "Friday"   },
                            {"September",30, "Monday"   },
                            {"October",  31, "Wednesday"},
                            {"November", 30, "Saturday" },
                            {"December", 31, "Monday"   }
                          };

struct year {                           /* year struct for 1997 */
               char *yearName;          /* string title */
               struct month *month;     /* pointer to array of month structs */
               short  initId;           /* initialization indicator */
            }  year1997;

struct date {
               char *monthName;
               short date;
            };

struct date glbMonthDate;               /* global monthDate struct */

/*
 *  Forward References/Prototypes
 */
int dayOfYear( struct date * );
int dateForDayNum( int, struct date * );
int daysBetween(struct date *,struct date *);

/*
 *  External References
 */
int abs( int );


/***********************************************************************
* Function:  calendar()
* Description: Illustrates some general calendar functions.
************************************************************************/
int calendar( int callParm )
{
	volatile char  *temp;
	volatile short  days;
	volatile int    status;
	volatile int    dayNumber, numOfDays;
	struct date firstDate, secondDate;   /* Local month date structures */
	struct date lclMonthDate;

	/*
	*  Initialize the year1997 structure
	*/
	year1997.yearName = "1997";
	year1997.month    = &MONTH[0];
	year1997.initId   = INITIALIZED;

	/*
	*  Setup 'temp' and 'days', useful to use as watch-window variables while stepping through the
	*  next set of instructions to illustrate how the structure is arranged.
	*/
	temp = year1997.yearName;

	temp = year1997.month[0].monthName;
	days = year1997.month[0].numOfDays;
	temp = year1997.month[0].startDay;

	temp = year1997.month[4].monthName;
	days = year1997.month[4].numOfDays;
	temp = year1997.month[4].startDay;

	temp = year1997.month[10].monthName;
	days = year1997.month[10].numOfDays;
	temp = year1997.month[10].startDay;

	/*
	*  Given a specific date, determine the 'day of the year'.
	*  For example, January 1, is day number one, December 31 is
	*  day 365 in 1997. If dayOfYear() returns a -1, then the year1997 structure
	*  was never properly initialized, that is, an error condition.
	*/
	glbMonthDate.monthName = "January";
	glbMonthDate.date      = 15;
	dayNumber = dayOfYear( &glbMonthDate );

	glbMonthDate.monthName = "October";
	glbMonthDate.date      = 13;
	dayNumber = dayOfYear( &glbMonthDate );

	glbMonthDate.monthName = "WINDober";     /* error case */
	glbMonthDate.date      = 30;
	dayNumber = dayOfYear( &glbMonthDate );


	/*
	*  Do the inverse operation of the operation above, that is,
	*  given a specific 'day number', calculate the month and day.
	*  For example, for day number 16, dateForDayNum returns
	*  January, 16th.  This function returns a 'status' that indicates
	*  if the date argument is legal. The month information is returned
	*  via the lclMonthDate argument.
	*/

	dayNumber = 134;          /* getting date for a legal day number */
	status = dateForDayNum( dayNumber, &lclMonthDate );

	/*
	* The locals window view of  'status' shows a valid dayNumber argument.
	* Also, either view the contents of lclMonthDate or view
	* the temp and days variables below.
	*/
	temp = lclMonthDate.monthName;
	days = lclMonthDate.date;

	/*
	* Try an invalid day number and check status in the local window.
	*/
	dayNumber = 366;
	status = dateForDayNum( dayNumber, &lclMonthDate );

	/*
	*  Given two dates, calculate the number of days between them,
	*  excluding the boundary dates. For example, the number of days
	*  between January 1 and January 3, is one day, excluding the boundary dates.
	*/
	firstDate.monthName = "June";
	firstDate.date = 17;
	secondDate.monthName = "September";
	secondDate.date = 23;

	numOfDays = daysBetween( &firstDate, &secondDate );

	return ((int) *temp);
}

/***********************************************************************
* Function: dayOfYear()
* Description: return the 'day number' given a month's day date.
************************************************************************/
int dayOfYear( struct date *monthDate )
{
	int n, daySum, status;

	/*
	*  Insure that the year1997 has been initialized, if not
	*  just return an error status.
	*/
	if ( year1997.initId != INITIALIZED )
	return -1;

	/*
	*  Find the month in the global year1997 structure
	*/
	for ( n=0, daySum=0; n < TWELVE_MONTHS ;n++ )
	{
		/*
		*  From the beginning of the year, accumulate the number of days
		*  in each month until the month name string argument matches
		*  the 1997 month string. Then then add in the month date argument
		*  to the running 1997 month total.
		*/
		status = strcmp( monthDate->monthName, year1997.month[n].monthName );

		if ( status == STRING_MATCH )
		{
			/*
			* Now add in the day offset. Check the desired date to
			* insure it lies within the month.  If not then return an error.
			*/
			if ( monthDate->date <= year1997.month[n].numOfDays )
			{
				daySum += monthDate->date;
				break;                           /* break out of for( ) loop    */
			}
			else
				return -1;
		}
		else
			daySum = daySum + year1997.month[n].numOfDays;
	}

	/*
	*  Check that the desired month was found in the above
	*  for() loop. If not return an error.
	*/

	daySum = ( n >= TWELVE_MONTHS ) ? -1 : daySum;

	return daySum;
}


/***********************************************************************
* Function:  dateForDayNum()
* Description: Returns month information given a specific day-number.
************************************************************************/
int dateForDayNum( int dayNumber, struct date *monthDate )
{
	int n;
	int badstatus = -1;

	/*
	* Check the dayNumber to make sure it's legal, returning an error if
	* out of range.
	*/
	if ((dayNumber < 0) || (dayNumber > 365))
		return badstatus;

	/*
	* Find the month for the dayNumber, implemented by subtracting off the number
	* of days when cycling through the months until dayNumber is less than or equal to
	* the new dayNumber.
	*/
	for ( n=0; n < TWELVE_MONTHS ;n++ )
	{
		if ( dayNumber > year1997.month[n].numOfDays )
			dayNumber -= year1997.month[n].numOfDays;
		else
			break;
	}

	/*
	* Make sure we have a reasonable answer.
	*/
	if ( n >= TWELVE_MONTHS )
		return badstatus;

	/*
	* It looks like we found the month.
	*/
	monthDate->monthName = year1997.month[n].monthName;
	monthDate->date = (short)dayNumber;

	return LEGITIMATE_DAYNUM;
}

/***********************************************************************
* Function:  daysBetween()
* Description: Returns the number of days between two given dates.
***********************************************************************/
int daysBetween( struct date *firstDate, struct date *secondDate )
{
	int numOfDays;
	int dayNum1, dayNum2;

	/*
	* Use 'dayOfYear()' function to calculate
	* the number of days between the two date arguments.
	*/
	dayNum1 = dayOfYear( firstDate );
	dayNum2 = dayOfYear( secondDate );

	/*
	*  Validate both arguments.
	*/

	if ((dayNum1 == -1) || (dayNum2 == -1))
	    numOfDays = -1;
 	else
	    numOfDays = abs( dayNum2 - dayNum1 );

	return numOfDays;
}
