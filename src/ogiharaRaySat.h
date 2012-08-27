/*! \file ogiharaRaySat.h
	\brief Defines function prototypes for Ogihara and Ray's algorithm.

*/

#ifndef OGIHARA_RAY_SAT_H_DEFINED
#define OGIHARA_RAY_SAT_H_DEFINED

#include "gel.h"
#include "executeTest.h"

gel get_UV_Sat( gel T, variable u, variable v, runtimeData & myData);
arguments ogiharaRaySat(const arguments myArgs);

#endif
