//
// Created by yijun on 9/21/16.
//

#include <gtest/gtest.h>
#include "LinearProgramming.h"

TEST(LinearProgrammingTest, LinearProgramming) {
    std::vector<std::vector<double>> A;
    std::vector<double> b;
    std::vector<double> c;
    LinearProgramming<double> linearProgramming;
    std::vector<double> feasibleSolution;
    feasibleSolution.resize(A.size());

    A = {{std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(),
          std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
         {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(),
          std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
         {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(),
          std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
         {std::numeric_limits<double>::lowest(), 2.0, -1.0, std::numeric_limits<double>::lowest(),
          std::numeric_limits<double>::lowest()},
         {std::numeric_limits<double>::lowest(), 1.0, -5.0, std::numeric_limits<double>::lowest(),
          std::numeric_limits<double>::lowest()},
    };

    b = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), 2, -4};
    c = {std::numeric_limits<double>::lowest(), 2, -1, std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()};
    double v = 0.0;


    feasibleSolution = linearProgramming.Simplex(A, b, c, v);

    for (std::vector<double>::iterator iter = feasibleSolution.begin(); iter != feasibleSolution.end(); iter++) {
        std::cout << "  " << *iter << " " << std::endl;
    }
    std::cout << std::endl;
}
