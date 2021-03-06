/*
 * Copyright (C) 2015  University of Alberta
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef SERVICES_H
#define SERVICES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "subsystems_ids.h"

/* PACKETS */
#define TM_TC_BUFF_SIZE 256
#define SUBSERVICE_BYTE 0
#define STATUS_BYTE 1
#define IN_DATA_BYTE 1
#define OUT_DATA_BYTE 2

/* SERVICES */
#define MAX_APP_ID 32     // number of CSP nodes (5-bits)
#define MAX_SERVICES 64   // number of CSP ports (6-bits)
#define MAX_SUBTYPES 256  // an 8-bit integer

typedef enum {
  OBC_APP_ID = _OBC_APP_ID_,
  EPS_APP_ID = _EPS_APP_ID_,
  ADCS_APP_ID = _ADCS_APP_ID_,
  COMMS_APP_ID = _COMMS_APP_ID_,
  GND_APP_ID = _GND_APP_ID_,
  DEMO_APP_ID = _DEMO_APP_ID_,
  LAST_APP_ID = _LAST_APP_ID_
} TC_TM_app_id;

typedef enum {
  SATR_PKT_ILLEGAL_APPID = 0,
  SATR_PKT_ILLEGAL_SUBSERVICE,
  SATR_OK,
  SATR_ERROR,
  SATR_RETURN_FROM_TASK,
  SATR_BUFFER_ERR,
  /*LAST*/
  SATR_LAST
} SAT_returnState;

/* services types & subtypes
 * Note: ports 0-7 are RESERVED by CSP. Don't use them.
 */

// TIME MANAGEMENT SERVICE
#define TC_TIME_MANAGEMENT_SERVICE 8
typedef enum {
  GET_TIME = 0,
  SET_TIME = 1
} Time_Management_Subtype;  // shared with EPS!

// HOUSEKEEPING SERVICE
#define TC_HOUSEKEEPING_SERVICE 9
typedef enum { TM_HK_PARAMETERS_REPORT = 0 } Housekeeping_Subtype;

// COMMUNICATION SERVICE
#define TC_COMMUNICATION_SERVICE 10
typedef enum { GET_TEMP = 0 } Communication_Subtype;

/* Utility definitions */
union _cnv {
  double cnvD;
  float cnvF;
  uint32_t cnv32;
  uint16_t cnv16[4];
  uint8_t cnv8[8];
};

SAT_returnState start_service_server(void);

#endif /* SERVICES_H */
