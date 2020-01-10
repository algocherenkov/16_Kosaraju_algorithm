#include "Kosaraju.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

//                   /````\
//                  /      v
//    0--->1------>2        3<-,
//    ^   /|       |^      /|  |
//    |  / |       | \,,,,/ |  |
//    | /  | /```\ |        |  |
//    |v   v/     vv        v  |
//    4--->5       6<-------7--`
//          ^     /
//           \,,,/

BOOST_AUTO_TEST_CASE(Kosaraju_test)
{
    std::vector<std::vector<int>> testGraph(8);
    testGraph[0].push_back(1);
    testGraph[1].push_back(2);
    testGraph[1].push_back(4);
    testGraph[1].push_back(5);
    testGraph[2].push_back(3);
    testGraph[2].push_back(6);
    testGraph[3].push_back(2);
    testGraph[3].push_back(7);
    testGraph[4].push_back(0);
    testGraph[4].push_back(5);
    testGraph[5].push_back(6);
    testGraph[6].push_back(5);
    testGraph[7].push_back(3);
    testGraph[7].push_back(6);

    auto resultFromRecursionAlgo = graphs::kosarajuRecursion(testGraph);

    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo.size() == 8, "wrong result size");
    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo[0] == resultFromRecursionAlgo[1], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo[1] == resultFromRecursionAlgo[4], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo[2] == resultFromRecursionAlgo[3], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo[3] == resultFromRecursionAlgo[7], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(resultFromRecursionAlgo[5] == resultFromRecursionAlgo[6], "vertices were not included in the component 2");

    auto resultFromIterativeAlgo = graphs::kosarajuIterative(testGraph);

    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo.size() == 8, "wrong result size");
    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo[0] == resultFromIterativeAlgo[1], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo[1] == resultFromIterativeAlgo[4], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo[2] == resultFromIterativeAlgo[3], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo[3] == resultFromIterativeAlgo[7], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(resultFromIterativeAlgo[5] == resultFromIterativeAlgo[6], "vertices were not included in the component 2");
}
BOOST_AUTO_TEST_SUITE_END()
