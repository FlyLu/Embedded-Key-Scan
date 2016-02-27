/***************************************************************************
 *   Copyright(C)2014-2015 by FlyLu <Linch.Embedded@gmail.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*============================ INCLUDES ======================================*/
#include ".\queue.h"
/*============================ MACROS ========================================*/
#define this        (*ptThis)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/


/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief is key queue enmty
 *! \param ptQueue key queue type
 *! \return ture  key queue is empty
 *! \return false key queue is not empty
 */ 
static bool is_queue_empty(key_queue_t *ptQueue);

/*! \brief key queue initialization
 *! \param ptQueue key queue type
 *! \param ptkey key type
 *! \param hwSize queue size 
 *! \return ture initialization success
 *! \return false initialization fail
 */
static bool init_queue(key_queue_t *ptQueue, key_t *ptkey, uint16_t hwSize);

/*! \brief key enqueue 
 *! \param ptQueue key queue type
 *! \param key_t key type
 *! \return ture enqueue success
 *! \return false enqueue fail
 */                  
static bool enqueue(key_queue_t *ptQueue, key_t tKey);

/*! \brief key dequeue 
 *! \param ptQueue key queue type
 *! \param ptkey key type 
 *! \return ture  dequeue success
 *! \return false dequeue fail
 */ 
static bool dequeue(key_queue_t *ptQueue, key_t *ptkey);

/*============================ GLOBAL VARIABLES ==============================*/
const i_queue_t QUEUE = {               //!< queue interface
    .Enqueue       = &enqueue,
    .Dequeue       = &dequeue,
    .IsEmpty       = &is_queue_empty,
    .Init          = &init_queue,
};

/*============================ IMPLEMENTATION ================================*/
/*! \brief key queue initialization
 *! \param ptQueue key queue type
 *! \param ptkey key type
 *! \param hwSize queue size 
 *! \return ture initialization success
 *! \return false initialization fail
 */
static bool init_queue(key_queue_t *ptQueue, key_t *ptkey, uint16_t hwSize)
{
	key_queue_t *ptThis = ptQueue;
	
    if (NULL == ptThis || NULL == ptkey) {
        return false;
    }

    this.ptBuffer   = ptkey;
    this.hwSize     = hwSize;
    this.hwHead     = 0;
    this.hwTail     = 0;
    this.hwLength   = 0;
   
    return true;
}


/*! \brief is key queue enmty
 *! \param ptQueue key queue type
 *! \return ture  key queue is empty
 *! \return false key queue is not empty
 */ 
static bool is_queue_empty(key_queue_t *ptQueue)
{
	key_queue_t *ptThis = ptQueue;

    if (NULL == ptThis) {
        return false;
    }

    return (0 == this.hwLength);
}


/*! \brief key enqueue 
 *! \param ptQueue key queue type
 *! \param key_t key type
 *! \return ture enqueue success
 *! \return false enqueue fail
 */                  
static bool enqueue(key_queue_t *ptQueue, key_t tKey)
{
	key_queue_t *ptThis = ptQueue;

    if (NULL == ptThis) {
        return false;
    }

    if (this.hwSize > this.hwLength) {          //!< queue is not full
        this.ptBuffer[this.hwTail++] = tKey;    //!< enter queue 
        this.hwLength ++;
        if (this.hwSize == this.hwTail) {
            this.hwTail = 0;
        }
        return true;
    }

    return false;    
}

/*! \brief key dequeue 
 *! \param ptQueue key queue type
 *! \param ptkey key type 
 *! \return ture  dequeue success
 *! \return false dequeue fail
 */ 
static bool dequeue(key_queue_t *ptQueue, key_t *ptkey)
{
	key_queue_t *ptThis = ptQueue;

    if (NULL == ptThis || NULL == ptkey) {
        return false;
    }

    if (0 != this.hwLength) {                    //!< queue is not empty
        *ptkey = this.ptBuffer[this.hwHead++];   //!< output queue
        this.hwLength --;
        if (this.hwSize == this.hwHead) {
            this.hwHead = 0;
        }
        return true;
    }

    return false;
}

/* EOF */
