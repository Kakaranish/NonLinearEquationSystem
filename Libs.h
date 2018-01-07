#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <utility>
#include <conio.h>
#include <algorithm>
#include <functional>

#define	converge_epsilon 10e-7
typedef std::function<double(std::vector<double>)> function_t;
typedef std::pair<double, function_t> pair_t;
