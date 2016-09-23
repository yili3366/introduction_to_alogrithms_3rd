//
// Created by yijun on 9/8/16.
//

#ifndef CHAP29_LINEARPROGRAMMING_H
#define CHAP29_LINEARPROGRAMMING_H

#include <vector>
#include <algorithm>
#include <set>
#include <functional>
#include <iostream>

template<typename T>
struct Node {
    int row;
    int column;
    T value;
};

template<typename T>
struct SlackForm {
    std::set<int> N;
    std::set<int> B;
    std::vector<std::vector<T>> A;

    std::vector<T> b;
    std::vector<T> c;
    T v;
};

template<typename T>
class LinearProgramming {
public:
    SlackForm<T> Pivot(std::set<int> N,
                       std::set<int> B,
                       std::vector<std::vector<T>> A,
                       std::vector<T> b,
                       std::vector<T> c,
                       T v,
                       int l,
                       int e);
    std::vector<T> Simplex(std::vector<std::vector<T>> A,
                           std::vector<T> b,
                           std::vector<T> c,
                           T v);

    SlackForm<T> InitializeSimplex(std::vector<std::vector<T>> A,
                                   std::vector<T> b,
                                   std::vector<T> c,
                                   T v);
private:
    void PrintLinearProgramming(SlackForm<T> slackForm);
    void PrintMatrix(std::vector<std::vector<T>> Matrix);
    void PrintVector(std::vector<T> vector);
    void PrintSet(std::set<int> set);
};

template<typename T>
SlackForm<T> LinearProgramming<T>::Pivot(std::set<int> N,
                                         std::set<int> B,
                                         std::vector<std::vector<T>> A,
                                         std::vector<T> b,
                                         std::vector<T> c,
                                         T v,
                                         int l,
                                         int e) {

    //Compute the coefficients of the question for new basic variable x.at(e).
    SlackForm<T> slackForm;
    std::vector<std::vector<T>> A1;
    std::vector<T> b1;
    std::vector<T> c1;
    T v1;

    std::set<int> N1;
    std::set<int> B1;

    slackForm.A = A;
    slackForm.B = B;
    slackForm.b = b;
    slackForm.c = c;
    slackForm.N = N;
    slackForm.v = v;

    b1.assign(b.size(), std::numeric_limits<T>::lowest());
    c1.resize(c.size(), std::numeric_limits<T>::lowest());
    A1.resize(A.size());

    for (typename std::vector<std::vector<T>>::iterator iter = A1.begin(); iter < A1.end(); iter++) {
        iter->assign(A.begin()->size(), std::numeric_limits<T>::lowest());
    }

    b1.at(e) = b.at(l) / A.at(l).at(e);

    for (std::set<int>::iterator iterN = N.begin(); iterN != N.end(); iterN++) {
        if (*iterN != e) {
            A1.at(e).at(*iterN) = A.at(l).at(*iterN) / A.at(l).at(e);
        }
    }
    A1.at(e).at(l) = 1 / A.at(l).at(e);

    // Compute the conefficients of the remaining constraints.
    for (std::set<int>::iterator iterB = B.begin(); iterB != B.end(); iterB++) {
        if (*iterB == l) {
            continue;
        }

        b1.at(*iterB) = b.at(*iterB) - A.at(*iterB).at(e) * b1.at(e);
        for (std::set<int>::iterator iterN = N.begin(); iterN != N.end(); iterN++) {
            if (*iterN != e) {
                A1.at(*iterB).at(*iterN) = A.at(*iterB).at(*iterN) - A.at(*iterB).at(e) * A1.at(e).at(*iterN);
            }
        }
        A1.at(*iterB).at(l) = -A.at(*iterB).at(e) * A1.at(e).at(l);
    }

    //Compute the objective function.
    v1 = v + c.at(e) * b1.at(e);

    for (std::set<int>::iterator iter = N.begin(); iter != N.end(); iter++) {
        if (*iter != e) {
            c1.at(*iter) = c.at(*iter) - c.at(e) * A1.at(e).at(*iter);
        }
    }

    c1.at(l) = -c.at(e) * A1.at(e).at(l);

    // Compute new sets of basic and nonbasic variables.
    for (std::set<int>::iterator iter = N.begin(); iter != N.end(); iter++) {
        if (*iter != e) {
            N1.emplace(*iter);
        }
    }
    N1.emplace(l);

    for (std::set<int>::iterator iter = B.begin(); iter != B.end(); iter++) {
        if (*iter != l) {
            B1.emplace(*iter);
        }
    }
    B1.emplace(e);

    slackForm.N = N1;
    slackForm.B = B1;
    slackForm.A = A1;
    slackForm.b = b1;
    slackForm.c = c1;
    slackForm.v = v1;

    return slackForm;
}

template<typename T>
std::vector<T> LinearProgramming<T>::Simplex(std::vector<std::vector<T>> A,
                                             std::vector<T> b,
                                             std::vector<T> c,
                                             T v) {
    SlackForm<T> slackForm;
    slackForm = InitializeSimplex(A, b, c, v);

    std::vector<T> feasibleSolution;
    feasibleSolution.assign(b.size(), std::numeric_limits<T>::lowest());

    if (slackForm.v == std::numeric_limits<T>::lowest()) { //infeasible
        return feasibleSolution;
    }

    std::vector<T> delta;
    delta.assign(slackForm.A.size(), std::numeric_limits<T>::max());

    while (std::find_if(slackForm.c.begin(),
                        slackForm.c.end(),
                        std::bind(std::greater<T>(), std::placeholders::_1, 0)) != slackForm.c.end()) {
        int e = std::numeric_limits<int>::lowest();

        for (std::set<int>::iterator iter = slackForm.N.begin(); iter != slackForm.N.end(); iter++) {
            if (slackForm.c.at(*iter) > 0) {
                e = *iter;
            }
        }

        for (std::set<int>::iterator iter = slackForm.B.begin(); iter != slackForm.B.end(); iter++) {
            if (slackForm.A.at(*iter).at(e) > 0) {
                delta.at(*iter) = slackForm.b.at(*iter) / slackForm.A.at(*iter).at(e);
            } else {
                delta.at(*iter) = std::numeric_limits<T>::max();
            }
        }

        int l = std::distance(delta.begin(), std::min_element(delta.begin(), delta.end()));

        if (delta.at(l) == std::numeric_limits<T>::max()) {
            for (int i = 1; i < A.size(); i++) {
                slackForm.B.emplace(i);
            }

            for (int i = 1; i < A.begin()->size(); i++) {
                slackForm.N.emplace(i);
            }

            slackForm.A = A;
            // clear A, Linear Programming L don't have optimal solution
//            slackForm.A.clear();
            slackForm.b = b;
            slackForm.c = c;
            slackForm.v = std::numeric_limits<T>::lowest();

            std::cout << " unbounded " << std::endl;

            return feasibleSolution;
        } else {
            slackForm = Pivot(slackForm.N, slackForm.B, slackForm.A, slackForm.b, slackForm.c, slackForm.v, l, e);
        }
    }

    for (int i = 0; i < A.begin()->size(); i++) {
        if (slackForm.B.find(i) != slackForm.B.end()) {
            feasibleSolution.at(i) = slackForm.b.at(i);
        } else {
            feasibleSolution.at(i) = 0;
        }
    }

    return feasibleSolution;
}


template<typename T>
SlackForm<T> LinearProgramming<T>::InitializeSimplex(std::vector<std::vector<T>> A,
                                                     std::vector<T> b,
                                                     std::vector<T> c,
                                                     T v) {
    int k;
    SlackForm<T> slackForm;
    SlackForm<T> Laux;
    SlackForm<T> L;

    //store original linear programming
    L.A = A;
    L.b = b;
    L.c = c;
    L.v = v;

    for (int i = 0; i < L.b.size(); i++) {
        if (L.b.at(i) != 0) {
            L.B.emplace(i);
        }
    }

    for (int i = 0; i < A.begin()->size(); i++) {
        L.N.emplace(i);
    }

    T minimal = std::numeric_limits<T>::max();
    for (int i = 0; i < b.size(); i++) {
        if (b.at(i) != std::numeric_limits<T>::lowest()) {
            if (b.at(i) < minimal) {
                minimal = b.at(i);
                k = i;
            }
        }
    }

    if (b.at(k) >= 0) {
        for (int i = 0; i < A.size(); i++) {
            slackForm.B.emplace(i);
        }

        for (int i = 0; i < A.begin()->size(); i++) {
            slackForm.N.emplace(i);
        }

        slackForm.A = A;
        slackForm.b = b;
        slackForm.c = c;
        slackForm.v = 0;

        return slackForm;
    }

    Laux.A = A;

    for (typename std::vector<std::vector<T>>::iterator iter = Laux.A.begin(); iter != Laux.A.end(); iter++) {
        if (std::count(iter->begin(), iter->end(), std::numeric_limits<T>::lowest()) != iter->size()) {
            *(iter->begin()) = -1;
        }
    }

    for (int i = 1; i < b.size(); i++) {
        if (b.at(i) != std::numeric_limits<T>::lowest()) {
            Laux.B.emplace(i);
        } else {
            Laux.N.emplace(i);
        }
    }

    //insert x0
    Laux.N.emplace(0);

    Laux.b = b;
    Laux.v = v;

    //insert x0
    Laux.c.assign(c.size(), std::numeric_limits<T>::lowest());
    for (typename std::set<int>::iterator iter = Laux.N.begin(); iter != Laux.N.end(); iter++) {
        Laux.c.at(*iter) = 0;
    }

    *Laux.c.begin() = -1;

    int l = k;

    // Laux has n + 1 nonbasic variables and m basic variables
    Laux = Pivot(Laux.N, Laux.B, Laux.A, Laux.b, Laux.c, Laux.v, l, 0);

    // The basic solution is now feasible for Laux.
    std::vector<T> delta;
    delta.assign(Laux.A.size(), std::numeric_limits<T>::max());

    while (std::find_if(Laux.c.begin(), Laux.c.end(), std::bind(std::greater<T>(), std::placeholders::_1, 0))
        != Laux.c.end()) {
        int e = std::numeric_limits<int>::lowest();

        for (std::set<int>::iterator iter = Laux.N.begin(); iter != Laux.N.end(); iter++) {
            if (Laux.c.at(*iter) > 0) {
                e = *iter;
            }
        }

        for (std::set<int>::iterator iter = Laux.B.begin(); iter != Laux.B.end(); iter++) {
            if (Laux.A.at(*iter).at(e) > 0) {
                delta.at(*iter) = Laux.b.at(*iter) / Laux.A.at(*iter).at(e);
            } else {
                delta.at(*iter) = std::numeric_limits<T>::max();
            }
        }

        int l = std::distance(delta.begin(), std::min_element(delta.begin(), delta.end()));

        if (delta.at(l) == std::numeric_limits<T>::max()) {
            for (int i = 0; i < A.size(); i++) {
                slackForm.B.emplace(i);
            }

            for (int i = 0; i < A.begin()->size(); i++) {
                slackForm.N.emplace(i);
            }

            slackForm.A = A;
            // clear A, Linear Programming L don't have optimal solution
//            slackForm.A.clear();
            slackForm.b = b;
            slackForm.c = c;
            slackForm.v = 0;

            std::cout << " unbounded " << std::endl;

            return slackForm;
        } else {
            Laux = Pivot(Laux.N, Laux.B, Laux.A, Laux.b, Laux.c, Laux.v, l, e);
        }
    }


    int x_0;
    if (Laux.b.at(0) != std::numeric_limits<T>::lowest()) {
        x_0 = Laux.b.at(0);
    } else {
        x_0 = 0;
    }

    if (x_0 == 0) {
        if (std::find(Laux.B.begin(), Laux.B.end(), 0) != Laux.B.end()) { // x0 is basic

            std::cout << " line " << __LINE__ << std::endl;
            for (int i = 0; i < Laux.A.begin()->size(); i++) {
                if (Laux.A.begin()->at(i) != 0) {

                    std::cout << " line " << __LINE__ << std::endl;
                    Pivot(Laux.N, Laux.B, Laux.A, Laux.b, Laux.c, Laux.v, 0, i);
                    break;
                }
            }
        }

        //remove x0, restore the original objective funciton
        Laux.B.clear();
        Laux.N.clear();
        Laux.c = L.c;

        for (typename std::vector<std::vector<T>>::iterator iter = Laux.A.begin(); iter != Laux.A.end(); iter++) {
            *(iter->begin()) = std::numeric_limits<T>::lowest();
        }

        for (int i = 1; i < Laux.b.size(); i++) {
            if (Laux.b.at(i) != std::numeric_limits<T>::lowest()) {
                Laux.B.emplace(i);
            } else {
                Laux.N.emplace(i);
            }
        }

        Laux.v = L.v;

        //restore the original objective function of L
        for (int i = 0; i < Laux.b.size(); i++) {
            if (Laux.b.at(i) != std::numeric_limits<T>::lowest() && L.c.at(i) != std::numeric_limits<T>::lowest()) {
                Laux.v = Laux.v + Laux.b.at(i) * L.c.at(i);

                for (typename std::set<int>::iterator iter = Laux.N.begin(); iter != Laux.N.end(); iter++) {
                    if (Laux.c.at(*iter) == std::numeric_limits<T>::lowest()) {
                        Laux.c.at(*iter) = 0;
                    }
                    Laux.c.at(*iter) = Laux.c.at(*iter) - Laux.A.at(i).at(*iter) * L.c.at(i);
                }
            }
        }

        for (typename std::set<int>::iterator iter = Laux.B.begin(); iter != Laux.B.end(); iter++) {
            Laux.c.at(*iter) = std::numeric_limits<T>::lowest();
        }

        return Laux;
    } else {
        std::cout << " infeasible " << std::endl;
        Laux.v = std::numeric_limits<T>::lowest();
        return Laux;
    }
}

template<typename T>
void LinearProgramming<T>::PrintLinearProgramming(SlackForm<T> slackForm) {
    std::cout << " print A " << std::endl;
    for (typename std::vector<std::vector<T>>::iterator outerIter = slackForm.A.begin(); outerIter != slackForm.A.end();
         outerIter++) {
        for (typename std::vector<T>::iterator innerIter = outerIter->begin(); innerIter != outerIter->end();
             innerIter++) {
            std::cout << "  " << *innerIter << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << " print B " << std::endl;
    for (std::set<int>::iterator iter = slackForm.B.begin(); iter != slackForm.B.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;

    std::cout << " print N " << std::endl;
    for (std::set<int>::iterator iter = slackForm.N.begin(); iter != slackForm.N.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;

    std::cout << " print b " << std::endl;
    for (typename std::vector<T>::iterator iter = slackForm.b.begin(); iter != slackForm.b.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;

    std::cout << " print c " << std::endl;
    for (typename std::vector<T>::iterator iter = slackForm.c.begin(); iter != slackForm.c.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;

    std::cout << " print v " << std::endl;
    std::cout << slackForm.v << std::endl;
}

template<typename T>
void LinearProgramming<T>::PrintMatrix(std::vector<std::vector<T>> matrix) {
    for (typename std::vector<std::vector<T>>::iterator outerIter = matrix.begin(); outerIter != matrix.end();
         outerIter++) {
        for (typename std::vector<T>::iterator innerIter = outerIter->begin(); innerIter != outerIter->end();
             innerIter++) {
            std::cout << "  " << *innerIter << "  ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void LinearProgramming<T>::PrintVector(std::vector<T> vector) {
    for (typename std::vector<T>::iterator iter = vector.begin(); iter != vector.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;
}

template<typename T>
void LinearProgramming<T>::PrintSet(std::set<int> set) {
    for (std::set<int>::iterator iter = set.begin(); iter != set.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;
}

#endif //CHAP29_LINEARPROGRAMMING_H
