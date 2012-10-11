#include <boost/test/auto_unit_test.hpp> 
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE TestModuleParser

#include <iostream>
#include <stdexcept>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <src/grammar.hpp>
#include <src/parser.hpp>
#include <src/ast.hpp>
#include <src/ast_debugger.hpp>

BOOST_AUTO_TEST_SUITE(TestModuleParser)

/**
 * Test Description: Test the parser behavior with empty strings.
 **/
BOOST_AUTO_TEST_CASE(TestCaseParserEmpty)
{
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

    std::string empty_1 = "";
    std::string empty_2 = "#this is a commentary";

    // parser should throw an exception, in case of an empty string.
    BOOST_REQUIRE_THROW(parser.execute(empty_1), std::invalid_argument);

    // parser should return true, in case of a string with only commentaries.
    BOOST_CHECK_EQUAL(parser.execute(empty_2), true);
}

///**
// * Test Description: The parser basic behavior.
// **/
//BOOST_AUTO_TEST_CASE(TestCaseParserBasic)
//{
//    //boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST); 
//    //xxon::Parser parser(*ast_ptr);
//
//    ///* test: one pair of key, value */
//    //std::string basic_1 = "my_key: 1";
//    //BOOST_CHECK_EQUAL(parser.execute(basic_1), true);
//    //BOOST_CHECK(ast_ptr->properties.find("my_key") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key"]), "1");
//
//    //std::string basic_2 = "my_key2: 45,\n\
//    //                       my_key3: 55";
//
//    ///* test: two pairs of key, value */
//    //BOOST_CHECK_EQUAL(parser.execute(basic_2), true);
//    //BOOST_CHECK(ast_ptr->properties.find("my_key2") != ast_ptr->properties.end());
//    //BOOST_CHECK(ast_ptr->properties.find("my_key3") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key2"]), "45");
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key3"]), "55");
//
//    //std::string basic_3 = "my_key4: True, #just a small comment!\n\
//    //                       my_key5: False";
//
//    ///* test: two pairs of key and value, with a commentary between them */
//    //BOOST_CHECK_EQUAL(parser.execute(basic_3), true);
//    //BOOST_CHECK(ast_ptr->properties.find("my_key4") != ast_ptr->properties.end());
//    //BOOST_CHECK(ast_ptr->properties.find("my_key5") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key4"]), "True");
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key5"]), "False");
//
//    //std::string basic_4 = "my_key6: True, my_key7: False, my_key8: False";
//
//    ///* test: multiple key, value in only one line */
//    //BOOST_CHECK_EQUAL(parser.execute(basic_4), true);
//    //BOOST_CHECK(ast_ptr->properties.find("my_key6") != ast_ptr->properties.end());
//    //BOOST_CHECK(ast_ptr->properties.find("my_key7") != ast_ptr->properties.end());
//    //BOOST_CHECK(ast_ptr->properties.find("my_key8") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key6"]), "True");
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key7"]), "False");
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["my_key8"]), "False");
//}
//
///**
// * Test Description: the intention behind this test is to check the parser
// * behavior when it's reading a xxon structure with multiple levels.
// */
//BOOST_AUTO_TEST_CASE(TestCaseParserHierarchy)
//{
//    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST); 
//    xxon::Parser parser(*ast_ptr);
//
//    std::string basic_string = "\
//    leve0: {\n\
//        level1: {\n\
//            level2: { my_key: 999, },\n\
//        },\n\
//    }";
//
//    BOOST_CHECK_EQUAL(parser.execute(basic_string), true);
//
//    BOOST_CHECK(ast_ptr->properties.find("leve0") != ast_ptr->properties.end());
//    xxon::AST* ast_level0 = boost::get<xxon::AST>(&ast_ptr->properties["leve0"]);
//    BOOST_CHECK(ast_level0);
//
//    BOOST_CHECK(ast_level0->properties.find("level1") != ast_level0->properties.end());
//    xxon::AST* ast_level1 = boost::get<xxon::AST>(&ast_level0->properties["level1"]);
//    BOOST_CHECK(ast_level1);
//
//    BOOST_CHECK(ast_level1->properties.find("level2") != ast_level1->properties.end());
//    xxon::AST* ast_level2 = boost::get<xxon::AST>(&ast_level1->properties["level2"]);
//    BOOST_CHECK(ast_level2);
//
//    BOOST_CHECK(ast_level2->properties.find("my_key") != ast_level2->properties.end());
//    BOOST_CHECK_EQUAL(boost::get<std::string>(ast_level2->properties["my_key"]), "999");
//}
//
///**
// * Test Description: This test checks if the parser is reading correctly an
// * structure with multiple lines, properties, comments and levels.
// **/
//BOOST_AUTO_TEST_CASE(TestCaseParserMultipleLines)
//{
//    //boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST); 
//    //xxon::Parser parser(*ast_ptr);
//
//    //std::string basic_string = "\
//    //    #just a comment\n\
//    //    key1: Hello My World!,\n\
//    //    key2: World,\n\
//    //    key3: { #starting a new block\n\
//    //        key3_1: Hello3_1, #another comment\n\
//    //        key3_2: Hello3_2,\n\
//    //        key3_3: Hello3_3,\n\
//    //        key3_4: Hello3_4,\n\
//    //    },\n\
//    //    key4: 40004,\
//    //    key5: Hello My World!,\n\
//    //    key6: {\n\
//    //        key6_1: Hello 6_1,\n\
//    //        key6_2: Hello 6_2,\n\
//    //        key6_3: {\n\
//    //            key6_3_1: Hello 6_3_1,\n\
//    //        },\n\
//    //        key6_4: Hello 6_3,\n\
//    //        key6_5: Hello 6_4,\n\
//    //    },\n\
//    //    key7: World";
//
//    //BOOST_CHECK_EQUAL(parser.execute(basic_string), true);
//
//    //BOOST_CHECK(ast_ptr->properties.find("key1") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["key1"]), "Hello My World!");
//
//    //BOOST_CHECK(ast_ptr->properties.find("key4") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["key4"]), "40004");
//
//    //BOOST_CHECK(ast_ptr->properties.find("key7") != ast_ptr->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_ptr->properties["key7"]), "World");
//
//    //BOOST_CHECK(ast_ptr->properties.find("key6") != ast_ptr->properties.end());
//    //xxon::AST* ast_key6 = boost::get<xxon::AST>(&ast_ptr->properties["key6"]);
//    //BOOST_CHECK(ast_key6);
//
//    //BOOST_CHECK(ast_key6->properties.find("key6_3") != ast_key6->properties.end());
//    //xxon::AST* ast_key6_3 = boost::get<xxon::AST>(&ast_key6->properties["key6_3"]);
//    //BOOST_CHECK(ast_key6_3);
//
//    //BOOST_CHECK(ast_key6_3->properties.find("key6_3_1") != ast_key6_3->properties.end());
//    //BOOST_CHECK_EQUAL(boost::get<std::string>(ast_key6_3->properties["key6_3_1"]), "Hello 6_3_1");
//}

BOOST_AUTO_TEST_SUITE_END();
