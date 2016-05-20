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
 * date.c - implements date handling routines
 */

#include "stdio.h"
#include "float.h"
#include "strutils.h"

char months[12][4] = {
    "JAN","FEB","MAR",
    "APR","MAY","JUN",
    "JUL","AUG","SEP",
    "OCT","NOV","DEC"
};

typedef struct ttime {
    int year;
    char month[10];
    char *day;
    int hour;
    int minute;
    int second;
} TIME;

typedef struct division {
    float div;
    float quo;
    double result;
} DIVISION;

int indexDate;

TIME clocker[1];
DIVISION division[1];

long send_month (char *sptr)
{
    char *index = "Test" \
                  " Locals";
    if ((strcmp(sptr, index)) != 0) return 0;
    if ((strcmp(sptr, "MAR")) == 0) return 0;
    return 1;
}

char date()
{
    TIME *full_time = (TIME *) &clocker ;
    DIVISION *ptr = (DIVISION *) &division;
    volatile long val = 0;
    indexDate = 7;

    val = send_month ( months[1]);


    full_time->year = 1996;

    strcpy (full_time->month, months[1]);

    full_time->day = "Friday";
    full_time->hour = 8;
    full_time->minute = 30;
    full_time->second = 15;


    ptr->quo = 12.02;
    ptr->div = 12.45;
    ptr->result = 1.00357737;

    return 'A';
}
