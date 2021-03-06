/*
Copyright (c) 2013-2014, Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory.
Written by Niklas Nielsen, Gregory Lee [lee218@llnl.gov], Dong Ahn.
LLNL-CODE-645136.
All rights reserved.

This file is part of DysectAPI. For details, see https://github.com/lee218llnl/DysectAPI. Please also read dysect/LICENSE

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (as published by the Free Software Foundation) version 2.1 dated February 1999.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "DysectAPI/Aggregates/Aggregate.h"
#include "DysectAPI.h"

using namespace std;
using namespace DysectAPI;

bool AggregateFunction::getParams(std::string fmt, std::vector<DataRef*>& params, va_list args) {
  const char* fmtStr = fmt.c_str();
  int len = fmt.size();
  bool next = false;
  char c;
  
  for(int i = 0; i < len; i++) {
    c = fmtStr[i];
    
    if(next) {
      switch(c) {
        case 'd': {
          const char* name = va_arg(args, const char*);
          params.push_back(new DataRef(Value::intType, name));
          next = false;
          break;
        }  
        case 'l': {
          const char* name = va_arg(args, const char*);
          params.push_back(new DataRef(Value::longType, name));
          next = false;
          break;
        }
        case 'f': {
          const char* name = va_arg(args, const char*);
          params.push_back(new DataRef(Value::floatType, name));
          next = false;
          break;
        }
        case 'L': {
          const char* name = va_arg(args, const char*);
          params.push_back(new DataRef(Value::doubleType, name));
          next = false;
          break;
        }
        case 'p': {
          const char* name = va_arg(args, const char*);
          params.push_back(new DataRef(Value::pointerType, name));
          next = false;
          break;
        }
        default:
          fprintf(stderr, "Unknown format specifier '%c'\n", c);
          return false;
          break;
      }
    } else if(c == '%') {
      next = true;
    }
  }
  
  return true;
}
