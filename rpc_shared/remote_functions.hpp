#pragma once

#include <vector>
#include <string>

//
// TODO: Declare your RPC functions here.
// Warning: Always provide a FunctionName__ARG_TYPES macro! Do not use references there!!!
//

#define RemoteFunction1__ARG_TYPES std::vector<double>, const char *
void RemoteFunction1(const std::vector<double> &, const char *);

#define RemoteFunction2__ARG_TYPES std::vector<double>, const char *
std::vector<std::string> RemoteFunction2(const std::vector<double> &, const char *);

#define RemoteFunction3__ARG_TYPES std::vector<double>, const char *
std::string RemoteFunction3(const std::vector<double> &, const char *);
