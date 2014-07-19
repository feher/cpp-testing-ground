#pragma once

#include <vector>
#include <string>
#include <unordered_map>

//
// TODO: Declare your RPC functions here.
//

void RemoteFunction1(const std::vector<double> &, const char *);
std::vector<std::string> RemoteFunction2(const std::string &, double);
std::string RemoteFunction3(const std::unordered_map<std::string, std::vector<float>> &, const short *);
