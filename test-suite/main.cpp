#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <iostream>

#include <boost/test/auto_unit_test.hpp> 
#include <boost/test/included/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp> 

bool init_unit_test()
{
    std::cout << "INIT" << std::endl;
    return true;
}

