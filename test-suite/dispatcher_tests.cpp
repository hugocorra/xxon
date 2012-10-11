//#include <boost/test/auto_unit_test.hpp> 
//#include <boost/test/unit_test.hpp>
//
//#define BOOST_TEST_MODULE TestModuleDispatcher
//
//#include <iostream>
//#include <vector>
//
//#include <boost/spirit/include/qi.hpp>
//
//#include <src/ast.hpp>
//#include <src/dispatcher.hpp>
//#include <src/parser.hpp>
//
//BOOST_AUTO_TEST_SUITE(TestModuleDispatcher)
//
///** 
// * Test Description: The parser have to read the str_xxon, create an AST tree 
// * and then the dispatcher should read the tree data.
// **/
//BOOST_AUTO_TEST_CASE(TestCaseOne)
//{
//    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
//    xxon::Parser parser(*ast_ptr);
//
//    std::string str_xxon = 
//       "person: {\
//            firstName: John,\
//            lastName: Smith,\
//            age: 25,\
//            address: {\
//                city: New York,\
//                state: NY,\
//                postalCode: 10021,\
//            },\
//        }";
//
//    BOOST_CHECK_EQUAL(parser.execute(str_xxon), true);
//
//    xxon::Dispatcher dispatcher;
//
//    auto address_handler = [] (xxon::AST &ast) -> bool
//    {
//        std::string city, state;
//        int postal_code;
//
//        BOOST_CHECK(ast.getDirective("city", city));
//        BOOST_CHECK(ast.getDirective("state", state));
//        BOOST_CHECK(ast.getDirective("postalCode", postal_code));
//
//        BOOST_CHECK_EQUAL(city,        "New York");
//        BOOST_CHECK_EQUAL(state,       "NY");
//        BOOST_CHECK_EQUAL(postal_code, 10021);
//        return true;
//    };
//
//    auto person_handler =  [&dispatcher] (xxon::AST &ast) -> bool
//    { 
//        std::string first_name, last_name;
//        int age;
//
//        BOOST_CHECK_EQUAL(dispatcher(ast), 1);
//        BOOST_CHECK(ast.getDirective("firstName", first_name));
//        BOOST_CHECK(ast.getDirective("lastName",  last_name));
//        BOOST_CHECK(ast.getDirective("age",       age));
//
//        BOOST_CHECK_EQUAL(first_name, "John");
//        BOOST_CHECK_EQUAL(last_name,  "Smith");
//        BOOST_CHECK_EQUAL(age, 25);
//
//        return true;
//    };
//
//    dispatcher.registerAST("person", person_handler);
//    dispatcher.registerAST("address", address_handler);
//    BOOST_CHECK_EQUAL(dispatcher(*ast_ptr), 1);
//}
//
//BOOST_AUTO_TEST_SUITE_END();