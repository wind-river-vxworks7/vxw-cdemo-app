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
 * main.c - main routine of C demo program
 */

/*
modification history
--------------------
01b,07jan11,mcm   Added support for X86_64
01a,07oct04,f_b   added
*/

#include "strutils.h"
#include <stdio.h>
#include <taskLib.h>

/*
 *  General Definitions
 */
#define BELL_CHAR  '\007'
#define MAX_LOCAL_STRING 5

typedef enum {red, yellow, blue} color_type;

typedef struct {
      short   a;
      char    b[16];
      int     c;
      color_type color;
    } REC_TYPE1;

REC_TYPE1 recordvar = {-1, "Wind River Tools", 987654321L, blue};

typedef struct test {
      int long_integer;
      short short_integer;
      int integer_array[4];
      char *string_pointer;
    } REC_TYPE2;

REC_TYPE2 rectest;

/*
 *  Externals
 */
extern char date( void );
extern int  engineers( int ), linkList ( int );
extern int  factorial( int ), fibonacci( int );
extern void factorialDemo( void ), fibonacciDemo( void );
extern int  calendar( int );

/*
 *  General Global Declarations
 */
short quick_index;
int   status, globalInt1;
int   globalLong1;
int   wait_count, wait_index;
int   initval;             /* initialization value for calculation */
char *globalstring[3];     /* Uninitializeded array of string pointers */

char bell[2] = {BELL_CHAR, '\0'};


/************************************************************************
* Function:    main()
* Description: Main entry point for the demonstration
*************************************************************************/
int main()
{
	volatile int  demo_counter;
	volatile int   pfa_demo=0;
	int   sum = 0;
	volatile char  cvar;              /* sample char variable */
	REC_TYPE1  q;
	volatile int   localInt1;
	volatile int  localLong1;

	/* Setup the global string array */
	globalstring[0] = "zero";
	globalstring[1] = "one";
	globalstring[2] = "two";

	/* Initialize the rectest structure */
	rectest.long_integer = 0xFFFFEEEE;
	rectest.short_integer = 5555;
	rectest.integer_array[0] = 0;
	rectest.integer_array[1] = 10;
	rectest.integer_array[2] = 20;
	rectest.integer_array[3] = 30;
	rectest.string_pointer = "Wind River's Tools Product Family";

	/*
	 *  Fill a table with factorials using recursive calls.
	 */
	factorialDemo( );

	/*
	 *  Fill a table with the fibonnacci sequence using recursive calls.
	 */
	fibonacciDemo( );

	/* set a local variable */
	pfa_demo = 3;

	/*
	 * Infinite Loop ...
	 * Could use demo_counter as a modulo-maxcount-for-sizeof(int)
	 * to count the iterations of the demo loop and view in a watch window.
	 */
    for ( demo_counter=0; TRUE ;demo_counter++ )
    {
    		printf ("demo_counter = %d\n", demo_counter);
		taskDelay (1);
		/*
		 *  Setup and examine 'engineer structure'. This function illustrates
		 *  arrays of structures and pointers to array of structures.
		 */
		status = engineers( 0x1234 );

		/*
		 *  Setup and examine link-list structure. This function illustrates
		 *  structure pointers and pointer-to-pointers.
		 */
		status = linkList( 0x5678 );

		/*
		 *  Calculate the factorial of a number. Since factorials
		 *  get very large quickly, only calculate the factorial
		 *  of the number 3 once every 25 iterations using the C modulo operator
		 *  to detect 25th iteration in the infinite loop.
		 *
		 *  Add 'demo_counter' in a watch window and set a breakpoint
		 *  on the 'localInt1=factorial(3);' line. If there are no other
		 *  enabled breakpoints in the loop, then every time the
		 *  run button is pressed, the demo_counter is updated.  But
		 *  the modulo operator filters calls to the factorial function
		 *  only once every 25 iterations through the loop.
		 */
		if ( !(demo_counter % 25) )
	        localInt1 = factorial( 3 );

		/*
		 *  Calculate the fibonacci of a fixed number, 5,
		 *  once every 100th iteration of the main test loop.
		 */
		if ( !(demo_counter % 100) )
	        globalInt1 = fibonacci( 5 );

		/*
		 *  Demonstrate some calendar functions.
		 */
		localLong1 = 0x12345678;

		globalLong1 = calendar( localLong1 );

		/*
		 *  Manipulate some local and  global structures.
		 */
		q.a = 55;
		strcpy(q.b,"December");
		q.c = 12345678L;
		q.color = red;

		sum = 0;
		wait_index  = 0;
		wait_count  = 5;
		quick_index = 5;

		recordvar.color = red;

		/*
		 *  Call a function written in assembler
		 */
		while (wait_index < wait_count)
		{
          wait_index++;
          sum = sum + 1;
		}

		cvar = date();
		recordvar.a = 0;

		for (quick_index = 0; quick_index <= 4 ;++quick_index) {
			++recordvar.a;
		}

		recordvar.color = blue;

		/*
		 * Before starting the demo_count loop once again, increment
		 * pfa_demo counter variable using a ternary condition operator.
		 * Also, maintain a modulo-3 range on its value.
		 */
		if (pfa_demo==3) {
			pfa_demo=0;
		} else {
			++pfa_demo;
		}
	}
	return 0;
}
