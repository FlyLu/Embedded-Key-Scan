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

#ifndef __KEY_H__
#define __KEY_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*============================ MACROS ========================================*/
//! \brief No key pressed
#define KEY_NULL        (0)

#define QUEUE_SIZE          (10)

#define KEY_SCAN_COUNT      (10000)

#define LONG_KEY_TIME       (50000)

#define KEY_REPEAT_TIME     (30000)
 
extern uint8_t get_key_scaned_value();
#define GET_KEY_SCANED_VALUE()  get_key_scaned_value()

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! \name key status enum type
//! @{ 
typedef enum {
    KEY_DOWN ,          //!< key press down
    KEY_UP,             //!< key release
    KEY_PRESSED,        //!< key pressed
    KEY_LONG_PRESSED,   //!< key long pressed
    KEY_REPEAT,         //!< key repeat
} key_status;
//! @}

//! \name key type 
//! @{
typedef struct {
    key_status tEvent;  //!< key type event
    uint8_t chKeyValue; //!< key value
} key_t;
//! @}

//! \name finit state machine state
//! @{
typedef enum {
    fsm_rt_err          = -1,    //!< fsm error, error code can be get from other interface
    fsm_rt_cpl          = 0,     //!< fsm complete
    fsm_rt_on_going     = 1,     //!< fsm on-going
    fsm_rt_wait_for_obj = 2,     //!< fsm wait for object
    fsm_rt_asyn         = 3,     //!< fsm asynchronose complete, you can check it later.
} fsm_rt_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief key initialization
 *! \param none
 *! \return none
 */
extern void key_init(void);

/*! \brief key task
 *! \param none
 *! \return none
 */
extern void key_task(void);

/*! \brief get key event
 *! \param ptKey key_t type pointer
 *! \return true get key event success
 *! \return false get key event fail
 */
extern bool get_key(key_t *ptKey);

/*============================ IMPLEMENTATION ================================*/

#endif 
/* EOF */
