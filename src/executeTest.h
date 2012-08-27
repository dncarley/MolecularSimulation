/*! \file executeTest.h
	\brief Defines function prototype for executeTest.

*/

#ifndef EXECUTE_TEST_H_DEFINED
#define EXECUTE_TEST_H_DEFINED

#include "arguments.h"
#include "verifySat.h"
#include "liptonSat.h"
#include "ogiharaRaySat.h"
#include "distributionSat.h"
#include <time.h>

arguments executeTest(const arguments myArgs);

#endif
