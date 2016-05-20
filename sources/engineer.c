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
 * engineer.c - implements 'Engineer Structure' routines
*/

#include "strutils.h"

/*
 *  Definitions
 */

#define MAX_NAME   10           /* Engineer information */
#define END_LIST   -1

typedef int  ENGINEER_ID;
typedef char ENGINEER_NAME;

struct engineer_struct {        /* Structure 'template/tag' */
                        ENGINEER_ID   id;
                        ENGINEER_NAME name[MAX_NAME];
                      };

/* Global array of engineer_structs */
struct engineer_struct hw_engineer[] = { {1, "Dick"   },
                                         {2, "Al"     },
                                         {3, "Charlie"},
                                         {END_LIST,"END"} };

/* Global array of pointers to engineer_structs */
struct engineer_struct *test_engineer[3];
struct engineer_struct TestEngineer = { 1, "Nick" };
struct engineer_struct SeniorTestEngineer = { 2, "Kirk" };
struct engineer_struct End = { END_LIST, "END" };


/************************************************************************
* Function:    engineers()
* Description: Manipulates the engineer structures.
* Notes:       - callParm is returned unaltered
*************************************************************************/
int engineers( volatile int callParm )
{
    ENGINEER_NAME engineer_name[MAX_NAME];
    volatile ENGINEER_ID   engineer_id;
    struct engineer_struct sw_eng1, sw_eng2;
    struct engineer_struct *sw_engineer[2];
    int n;

    /*
     *  Examine the global hardware engineer array of structs,
     *  and the locals engineer_name and engineer_id.
     *  The array of hardware engineer structs is delimited by an end
     *  record, equal to END_LIST.
     *
     */
    for (n=0; hw_engineer[n].id != END_LIST ;n++ )
    {
      strcpy (engineer_name, hw_engineer[n].name );
      engineer_id = hw_engineer[n].id;
    }

    /* Setup a software engineer array of pointers to engineer_structs */
    sw_eng1.id = 4;                   /* initialize the first struct */
    strcpy(sw_eng1.name,"Dennis");

    sw_eng2.id = 5;
    strcpy(sw_eng2.name,"JCC");       /* initialize the second struct */

    sw_engineer[0] = &sw_eng1;        /* initialize array of pointers */
    sw_engineer[1] = &sw_eng2;

    /* Examine the locals with the debugger */
    strcpy(engineer_name, sw_engineer[0]->name);
    engineer_id = sw_engineer[0]->id;

    strcpy(engineer_name, sw_engineer[1]->name);
    engineer_id = sw_engineer[1]->id;

    /* Setup a global test engineer array of pointers to engineer_struct */
    test_engineer[0] = &TestEngineer;
    test_engineer[1] = &SeniorTestEngineer;
    test_engineer[2] = &End;                  /* End-of-list terminator */

    /* Examine the locals */
    for (n=0; test_engineer[n]->id != END_LIST ;n++ )
    {
        strcpy(engineer_name, test_engineer[n]->name);
        engineer_id = test_engineer[n]->id;
    }

    return callParm;
}  /* end of engineerStructs() */
