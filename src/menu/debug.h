/* -*- C++ -*- */
#pragma once
/**
* @file menu.h
* @author Rui Azevedo
* @date 10 May 2019
* @copyright 2019 Rui Azevedo
* @brief ArduinoMenu output implementations
*/

#ifdef MENU_DEBUG
  #ifdef ARDUINO
    #include <streamFlow.h>
    #ifndef MDO
      #define MDO Serial
    #endif
  #else
    #include <iostream>
    using namespace std;
    #ifndef MDO
      #define MDO cout
    #endif
  #endif
#endif

#if defined(MENU_DEBUG) && defined(TRACE)
  #define trace(x) x
#else
  #define trace(x)
#endif
#ifdef MENU_DEBUG
  #define _trace(x) x
#else
  #define _trace(x)
#endif
#ifndef MENU_RELEASE
  #define __trace(x) x
#else
  #define __trace(x)
#endif

#include <assert.h>
#ifdef ARDUINO

  //from: https://gist.github.com/jlesech/3089916
  #if !defined(__AVR_ATtiny13__) && !defined(ATTINY_CORE)
    #define __ASSERT_USE_STDERR

    // handle diagnostic informations given by assertion and abort program execution:
    void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
        // transmit diagnostic informations through serial link.
        Serial.println(__func);
        Serial.println(__file);
        Serial.println(__lineno, DEC);
        Serial.println(__sexp);
        Serial.flush();
        // abort program execution.
        abort();
    }
  #endif

#endif
