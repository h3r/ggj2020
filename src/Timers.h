#ifndef TIMERS_H
#define TIMERS_H

/*******************************************************************//**
*
* @file     Timers.h
*
* @author   Xavier Del Campo
*
* @brief    Include file for Timers module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

/* *************************************
 * Defines
 * *************************************/

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* *************************************
 * Public types definition
 * *************************************/

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

EXTERNC void TimersInit(void);
EXTERNC unsigned int RootCounter1Get(void);
EXTERNC unsigned int RootCounter2Get(void);

#endif /* TIMERS_H */
