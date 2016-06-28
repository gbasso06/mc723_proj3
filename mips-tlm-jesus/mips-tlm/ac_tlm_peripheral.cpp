/**
 * @file      ac_tlm_mem.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ac_tlm_peripheral.h"
#include <byteswap.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate peripheral from ArchC
using user::ac_tlm_peripheral;

/// Define matrix size
#define N 32

/// Define two matriz to receive data
int matriz1[N][N]; int matriz2[N][N];
int result[N][N];

/// define two counters to iterate on the matriz to store values
int count = -1; int count2 = -1;

int count_retrieve = -1;
/// Constructor
ac_tlm_peripheral::ac_tlm_peripheral( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the peripheral
    target_export( *this );
}

int value = 0;
//int result, operand1, operand2;
int operand1, operand2;

/// Destructor
ac_tlm_peripheral::~ac_tlm_peripheral() {
  int i, j = 0;
  for(i = 0; i < N; i++){
    for (j = 0; j <N;j++){
      result[i][j] = 0;
    }
  }
}

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d is the data being write
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d )
{

    int i, j, l, aux = 0;
    if ((*(uint32_t *) &a) == 0xc900000 ){
      count++;
      operand1 = bswap_32(d);
      matriz1[count / N][count % N] = operand1;
      return SUCCESS;
    }
    //OPERAND2 ADDRESS DEFINED IN SW
    if ((*(uint32_t *) &a) == 0xca00000 ){
      count2++;
      operand2 = bswap_32(d);
      matriz2[count2 / N][count2 % N] = operand2;
      return SUCCESS;
    }
  
  //cout << "addr: " <<  std::hex  << a << " data: " << d << endl;
  value = d;
  return SUCCESS;
}

/** Internal Read
  * Note: Always read 32 bits
  * @param a is the address to read
  * @param d id the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  int i, j, l, aux = 0;

  if ((*(uint32_t *) &a) == 0xcb00000 ){
    // cout << "RESULT:" << hex << result << endl;
    //result = operand1*operand2;

    /*
    printf("matriz1: \n");
    for(i = 0; i < N; i++){
      for (j = 0; j <N;j++){
        printf("%d, ", matriz1[i][j]);
      }
      printf("\n");
    }
    printf("\n");

    printf("matriz2: \n");
    for(i = 0; i < N; i++){
      for (j = 0; j <N;j++){
        printf("%d, ", matriz2[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    */
    if (result[0][0] == 0){
      for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
          aux = 0;
          for(l = 0; l < N; l++){
            aux += matriz1[i][l] * matriz2[l][j];
          }
          result[i][j] = aux;
        }
      }
    }
    wait(70,SC_NS); //TIME DEFINED BY USER : TIME REQUIRED BY HW_MODULE TO CALCULATE A VALUE

    /*
    printf("resultado: \n");
    for(i = 0; i < N; i++){
      for (j = 0; j <N;j++){
        printf("%d, ", result[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    */
    wait(70,SC_NS); //TIME DEFINED BY USER : TIME REQUIRED BY HW_MODULE TO CALCULATE A VALUE

    //*((uint32_t *) &d) = bswap_32(result); // d = bswap_32(result);
    //printf("&result: %d\tresult[0][0]: %d\tresult: %d\n", &result, result[0][0], result);
    count_retrieve++;
    *((uint32_t *) &d) = bswap_32(result[count_retrieve / N][count_retrieve % N]);
    // cout << "D: " << *((uint32_t *) &d) << endl;
    return SUCCESS;

  } else {
    d = value;
    value = 1;
    return SUCCESS;
  }
}
