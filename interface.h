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

#ifndef __KEY_INTERFACE_H__
#define __KEY_INTERFACE_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
//! \brief No key pressed
#define KEY_NULL        (0)

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

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

#endif
/* EOF */