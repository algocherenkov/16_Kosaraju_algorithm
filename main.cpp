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

BOOST_AUTO_TEST_CASE(Kosaraju_test)
{
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

    auto result = graphs::kosaraju(testGraph);

    BOOST_CHECK_MESSAGE(result.size() == 8, "wrong result size");
    BOOST_CHECK_MESSAGE(result[0] == result[1], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(result[1] == result[4], "vertices were not included in the component 0");
    BOOST_CHECK_MESSAGE(result[2] == result[3], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(result[3] == result[7], "vertices were not included in the component 1");
    BOOST_CHECK_MESSAGE(result[5] == result[6], "vertices were not included in the component 2");
}
BOOST_AUTO_TEST_SUITE_END()
