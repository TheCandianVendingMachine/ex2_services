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
 /**
  * @file services.h
  * @author upSat, Andrew Rooney, Thomas Ganley
  * @date 2020-07-14
  */


#ifndef SERVICES_H
#define SERVICES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <csp/csp.h>

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

#define MAX_PKT_LEN 210 // TODO: What is our max packet length?
#define MAX_PKT_SIZE (MAX_PKT_LEN * 1) // TODO: what is our packet type?

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
  SATR_SCHS_FULL,
  SATR_SCHS_INTRL_LGC_ERR,
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
#define TC_EVENT_SERVICE 10
#define TC_FUNCTION_MANAGEMENT_SERVICE 11
#define TC_SCHEDULING_SERVICE 13
typedef enum { TM_HK_PARAMETERS_REPORT = 0 } Housekeeping_Subtype;

// COMMUNICATION SERVICE
#define TC_COMMUNICATION_SERVICE 10
typedef enum { GET_TEMP = 0 } Communication_Subtype;

/*SCHEDULING SERVICE*/
#define SCHS_ENABLE_RELEASE             1 /*subservice 01, Telecommand to enable the release of telecommands from schedule pool*/
#define SCHS_DISABLE_RELEASE            2 /*subservice 02, Telecommand to disable the release of telecommands from schedule pool*/
#define SCHS_RESET_POOL                 3 /*subservice 03, Telecommand to reset the schedule pool*/
#define SCHS_INSERT_ELEMENT             4 /*subservice 04, Telecommand to insert a tc_tm_pkt in schedule pool*/
#define SCHS_REMOVE_ELEMENT             5 /*subservice 05, Telecommand to delete a tc_tm_pkt from schedule pool*/
#define SCHS_TIME_SHIFT_SEL             6 /*subservice 06, Telecommand to time shift (+/-) selected active schedule packet*/
#define SCHS_TIME_SHIFT_ALL             7 /*subservice 07, Telecommand to time shift (+/-) all schedule packets*/
#define SCHS_DETAILED_SCH_REPORT        8 /*subservice 08, Telemetry response (to subservice 10)*/
#define SCHS_SIMPLE_SCH_REPORT          9 /*subservice 09, Telemetry response (to subservice 11)*/
#define SCHS_REPORT_SCH_DETAILED        10 /*subservice 10, Telecommand to report schedules in detailed form*/
#define SCHS_REPORT_SCH_SUMMARY         11 /*subservice 11, Telecommand to report schedules in summary form*/
#define SCHS_LOAD_SCHEDULES             12 /*subservice 12, Telecommand to load schedules from perm storage*/
#define SCHS_SAVE_SCHEDULES             13 /*subservice 13, Telecommand to save schedules on perm storage*/



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
