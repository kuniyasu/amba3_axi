/*
 * main.cpp
 *
 *  Created on: 2014/01/04
 *      Author: Kuniyasu
 */

#include "TOP.h"

TOP* top;

int sc_main(int argc, char* argv[]){
	top = new TOP("top");
	sc_start();
	return 0;
}


