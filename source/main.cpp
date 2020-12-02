// Copyright (c) 2020 Milan Raj
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <iostream>
#include <string>

#include <emscripten.h>
#define EXPORT extern "C" EMSCRIPTEN_KEEPALIVE

double doFancyAlgorithm() {
   std::cerr << "out of band message";
   return 42;
}

extern "C" {
   extern double fancyAlgorithm();
}

EXPORT double fancyAlgorithm() {
   double result = doFancyAlgorithm();
   fflush(NULL);
   return result;
}

int main(int argc, char* argv[])
{
   // TODO strange things happen when running as a library in browsers if main is never called.
   // Find a way to control setup without needing to run main and immediately return
   std::string exitFlag("--exit");
   for (int i = 0; i < argc; i++) {
      std::string currentFlag(argv[i]);
      if (currentFlag == exitFlag) {
         return 0;
      }
   }

   for ( ; ; )
   {
      std::string input;

      std::cout << ">> ";
      std::getline(std::cin,input);

      if (input.empty())
         continue;
      else if (input.find("exit") == 0)
         break;
      else if (input.find("quit") == 0)
         break;

      double result = doFancyAlgorithm();
      printf("input(%f): %s\n", result, input.c_str());
   }

   return 0;
}
