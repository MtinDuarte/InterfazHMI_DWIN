/*
 * conf_ATCmds.h
 *
 *  Created on: Sep 18, 2022
 *      Author: Martin
 */

#ifndef SRC_AF_1_CONFIG_CONFIG_CONF_ATCMDS_H_
#define SRC_AF_1_CONFIG_CONFIG_CONF_ATCMDS_H_


/**
 * @brief Tests AT startup.
 */
static const char AT_COMMAND [] = "AT\r\n";
static const char AT_RESET[] = "AT+RST\r\n";
/**
 * @brief Checks version information
 *
 */
static const char AT_GMR[] = "AT+GMR\r\n";
/**
 * @brief Enters Deep-Sleep mode.
 *
 */
static const char AT_GSLP[] = "AT+GSLP";
/**
 * @brief Restores the factory default settings of the module
 *
 */
static const char AT_RESTORE[] = "AT+RESTORE\r\n";
/**
 * @brief The current UART configuration
 *
 */
//static const char AT_UART_CUR[]= "AT+UART_CUR\r\n";
//static const char AT_CWMODE_SOFT_AP_MODE []  = "AT+CWMODE=2\r\n";
//static const char AT_CWMODE_SOFTAP_PLUS_STATIONMODE []  = "AT+CWMODE=3\r\n";
static const char AT_CWMODE_STATION_MODE []  = "AT+CWMODE=1\r\n";
/**
 * @brief Ask current IP and MAC address
 *
 */
static const char AT_CIFSR [] = "AT+CIFSR";
static const char AT_CIPMUX[] = "AT+CIPMUX";
//#define AT_CWJAP(ssid,password) "AT+CWJAP=\"ssid\",\"password\""


static const char Speakers_Topic [] = "Speakers";

#endif /* SRC_AF_1_CONFIG_CONFIG_CONF_ATCMDS_H_ */
