/***************************************************************************
 *   Copyright(C)2014-2015 by FlyLu <fly.lu@iStarChip.com>                 *
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

#ifndef __QUEUE_H__
#define __QUEUE_H__

/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"
#include ".\interface.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*! \brief key queue initialization
 *! \param __QUEUE key queue type
 *! \param __BUFFER key type
 *! \param __SIZE queue size 
 *! \return ture initialization success
 *! \return false initialization fail
 */
#define INIT_KEY_QUEUE(__QUEUE, __BUFFER, __SIZE)                              \
                                          QUEUE.Init(__QUEUE, __BUFFER, __SIZE)
/*! \brief key enqueue 
 *! \param __QUEUE key queue type
 *! \param __TYPE key type
 *! \return ture enqueue success
 *! \return false enqueue fail
 */                                          
#define KEY_ENQUEUE(__QUEUE, __TYPE)      QUEUE.Enqueue(__QUEUE, __TYPE)   
                                            
/*! \brief key dequeue 
 *! \param __QUEUE key queue type
 *! \param __ADDR key type 
 *! \return ture  dequeue success
 *! \return false dequeue fail
 */ 
#define KEY_DEQUEUE(__QUEUE, __ADDR)      QUEUE.Dequeue(__QUEUE, __ADDR)
                                            
/*! \brief is key queue enmty
 *! \param __QUEUE key queue type
 *! \return ture  key queue is empty
 *! \return false key queue is not empty
 */ 
#define IS_KEY_QUEUE_EMPTY(__QUEUE)       QUEUE.IsEmpty(__QUEUE) 

/*============================ TYPES =========================================*/
//! \name key queue type
//! @{                                            
DEF_CLASS(key_queue_t)
    key_t   *ptBuffer; 
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;
END_DEF_CLASS(key_queue_t)
//! @}

//! \name queue interface
//! @{
DEF_INTERFACE(i_queue_t)
    bool (*IsEmpty)(key_queue_t *ptQueue);
    bool (*Enqueue)(key_queue_t *ptQueue, key_t tKey);
    bool (*Dequeue)(key_queue_t *ptQueue, key_t *ptkey);
    bool (*Init)(key_queue_t *ptQueue, key_t *ptkey, uint16_t hwSize);
END_DEF_INTERFACE(i_queue_t)
//! @}

/*============================ GLOBAL VARIABLES ==============================*/ 
extern const i_queue_t QUEUE;   //!< queue interface 

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

#endif
/* EOF */


