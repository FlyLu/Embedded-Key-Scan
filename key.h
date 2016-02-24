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

#ifndef __KEY_H__
#define __KEY_H__

/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"
#include ".\interface.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
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
