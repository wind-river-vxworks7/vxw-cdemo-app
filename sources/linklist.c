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
 * linklist.c - implements link list demonstration
 */

/*
 *  Definitions
 */
#define NULL   ( void *)0

/*
 *  Cell Structure Template
 */
struct cell_struct {
                     int    IdNum;               /* cell ID number      */
                     char   IdLetter;            /* cell ID letter      */
                     struct cell_struct *next;   /* pointer to next     */
                     struct cell_struct *prev;   /* pointer to previous */
                   };
/*
 *  Global cell_structs
 */
struct cell_struct cell_1, cell_2, cell_3;           /* Uninitialized */

struct cell_struct cell_4 = { 4, 'D', NULL, NULL };  /* Initialized  */

/*
 *  Forward References
 */
void  addCell   ( struct cell_struct *, struct cell_struct * );
void  swapCells ( struct cell_struct *, struct cell_struct * );


/************************************************************************
* Function:    linklist()
* Description: Manipulates Link Lists
************************************************************************/
int linkList( int callParm )
{
  struct cell_struct *cell_ptr;      /* local pointer to cell list   */
  volatile struct cell_struct cell;  /* local cell structure (note1) */
  volatile int genLocal;             /* (note2)                      */
  int n;

  genLocal = callParm;              /* callParm is examined, but not used */

  /*
   * Initialize and arrange the cells into a doubly-linked circular list.
   * The debugger can be used to verify each initialization step.
   * However, be careful of uninitialized values. For example, the 'next'
   * and 'prev' values are pointers that may point to illegal memory areas
   * prior to initialization.
   */
  cell_1.IdNum = 1;
  cell_1.IdLetter = 'A';
  cell_1.next = &cell_2;
  cell_1.prev = &cell_3;

  cell_2.IdNum = 2;
  cell_2.IdLetter = 'B';
  cell_2.next = &cell_3;
  cell_2.prev = &cell_1;

  cell_3.IdNum = 3;
  cell_3.IdLetter = 'C';
  cell_3.next = &cell_1;
  cell_3.prev = &cell_2;

 /*
  * Now that all of the elements have been initialized, the debugger can be
  * used to examine some items. For example, highlighting 'cell_3' will
  * display all of cell_3's elements. Highlighting 'cell_3.prev' will
  * display all of cell_2's elements. Highlighting 'cell_3.next' will
  * display cell_1's elements -- recall it is a circular list.
  */

 /*
  * We can also use a local cell_struct pointer to cycle through the
  * list automatically. Since the last cell is linked back to the first,
  * there is no 'end' to the list.
  *
  * One way of setting up the debugger to view these steps is to have
  * 'cell' and/or 'cell_ptr' as watch-window variables.
  */
  cell_ptr = &cell_1;             /* point to the first cell */

  for (n=0; n < 6 ;n++)
  {
    cell.IdNum = cell_ptr->IdNum;
    cell.IdLetter = cell_ptr->IdLetter;
    cell.next = cell_ptr->next;
    cell.prev = cell_ptr->prev;

    cell_ptr = cell.next;        /* point to the next cell in the list */
  }

 /*
  *  Add a new cell and then rearrange the order of the link list.
  */

 /*
  *  First, add one more cell to the end of the list -- cell_4.
  *  The cells will now be numbered: 1, 2, 3, and 4.  Recall, cell_4 was
  *  initialized at declaration time.
  *
  *  addCell() uses pointer-to-pointer constructs to add the new
  *  cell. 'step into' the function to see how  this done.
  */
  addCell( &cell_4, &cell_3 );

 /*
  *  Second, swap cells #2 and #3 in the link order. The cells will
  *  now be numbered: 1, 3, 2, and 4.
  *
  *  WARNING:  Do not step into this function, it contains complex
  *            data constructs.
  */
  swapCells( &cell_2, &cell_3);

 /*
  *  Now, let's sequence through the linked list, once, to insure
  *  the above operations have been performed.
  */
  cell_ptr = &cell_1;             /* point to the first cell */

  for (n=0; n < 4 ;n++)
  {
    cell.IdNum = cell_ptr->IdNum;
    cell.IdLetter = cell_ptr->IdLetter;
    cell.next = cell_ptr->next;
    cell.prev = cell_ptr->prev;

    cell_ptr = cell.next;        /* point to the next cell in the list */
  }

 /*
  * If you did not step into the addCell() or swapCells() functions, you
  * may have missed the pointer-to-pointer examples. Let's use a similar
  * concept here to view the cell information of where the next cell in the
  * sequence 'points to'. Recall, the current list order is 1,3,2,4. Assuming
  * the current cell is the first cell, cell_1, then it is easy to view
  * cell_3's information via cell_1's 'next' pointer. However, we can also
  * view cell_2's information from cell_1 via a pointer-pointer:
  *            i.e.  cell_1->next->next->element construct.
  *
  * (Ok, you caught me, this is actually a pointer to a structure which
  *  has a pointer that points to another structure, which also has a
  *  pointer to yet another structure --- or a pointer-pointer-pointer)
  *
  * Like the previous steps, having 'cell' and 'cell_ptr' as watch-window
  * variables are useful for viewing the results.
  */
  cell_ptr = &cell_1;               /* point to the first cell */

  cell.IdNum = cell_ptr->next->next->IdNum;       /* peek at the values */
  cell.IdLetter = cell_ptr->next->next->IdLetter;
  cell.next = cell_ptr->next->next->next;
  cell.prev = cell_ptr->next->next->prev;

  return callParm;
} /* end of linklist() */


/*************************************************************************
* Function:     addCell()
* Description:  Adds a new cell into the linked list
* Notes:        - The first argument of addCell is a pointer to the
*                 new cell and the section argument is a pointer to the
*                 cell that the new one will be added after.
*/
void  addCell( struct cell_struct *new_cell, struct cell_struct *old_cell )
{
   new_cell->next = old_cell->next;
   new_cell->prev = old_cell;

   old_cell->next->prev = new_cell;        /* pointer-pointer example */

   old_cell->next = new_cell;
}

/*************************************************************************
* Function:     swapCells()
* Description:  swaps the two cells passed in.
*               - To swap two cells:
*                   a.) for both cells, adjust the previous cell's 'next'
*                       pointer. Use a pointer-pointer.
*                   b.) for both cells, adjust the next cell's 'prev'
*                       pointer. Use a pointer-pointer.
*                   c.) swap both cells internal next and prev pointers.
*                       Use a temp variable to hold intermediate values.
*************************************************************************/
void  swapCells( struct cell_struct *cellA, struct cell_struct *cellB )
{
  struct cell_struct *ptemp;

  /* !!! I KNEW YOU COULDN'T RESIST !!! */

  cellA->prev->next = cellB;          /* step a */
  cellB->prev->next = cellA;

  cellA->next->prev = cellB;          /* step b */
  cellB->next->prev = cellA;

  ptemp = cellA->next;                /* step c */
  cellA->next = cellB->next;
  cellB->next = ptemp;

  ptemp = cellA->prev;
  cellA->prev = cellB->prev;
  cellB->prev = ptemp;
}
