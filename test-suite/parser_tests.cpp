#include <boost/test/auto_unit_test.hpp> 
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE TestModuleParser

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant/get.hpp>

#include <src/grammar.hpp>
#include <src/parser.hpp>
#include <src/ast.hpp>
#include <src/ast_debugger.hpp>
#include <src/handler.hpp>


BOOST_AUTO_TEST_SUITE(TestModuleParser)

/**
 * Test Description: Test the parser behavior with empty strings.
 **/
BOOST_AUTO_TEST_CASE(TestCaseParserEmpty)
{
    boost::shared_ptr<xxon::AST> ast(new xxon::AST);
    xxon::Parser parser(*ast);

    std::string empty_1 = "";

    // parser should return true, in case of a string with only commentaries.
    BOOST_CHECK_EQUAL(parser.execute(empty_1), true);
    //BOOST_CHECK_EQUAL(ast->exists(), false);
}

BOOST_AUTO_TEST_CASE(TestCaseParserEmptyDict)
{
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

    std::string empty_dict = "{}";

    BOOST_CHECK_EQUAL(parser.execute(empty_dict), true);
    BOOST_REQUIRE_EQUAL(ast_ptr->exists(), true);

 //   BOOST_CHECK_EQUAL(boost::apply_visitor(xxon::collectionSize(), ast_ptr->collection), 0);
}

BOOST_AUTO_TEST_CASE(TestCaseParserEmptyList)
{
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

    std::string empty_list = "[]";

    BOOST_CHECK_EQUAL(parser.execute(empty_list), true);
    BOOST_REQUIRE_EQUAL(ast_ptr->exists(), true);

 //   BOOST_CHECK_EQUAL(boost::apply_visitor(xxon::collectionSize(), ast_ptr->collection), 0);
}

BOOST_AUTO_TEST_CASE(TestCaseParserListSize)
{
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

    std::string str_list = "[1,true,false,4,\"Hello\"]";

    BOOST_CHECK_EQUAL(parser.execute(str_list), true);
    BOOST_REQUIRE_EQUAL(ast_ptr->exists(), true);

    xxon::List* list = boost::get<xxon::List>(&ast_ptr->collection);//boost::apply_visitor(get_list(), ast_ptr->collection);

    BOOST_REQUIRE(list != NULL);
    BOOST_CHECK_EQUAL(list->size(), 5);
}

BOOST_AUTO_TEST_CASE(TestCaseParserDictElements)
{
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

    std::string str_dict = "{\"name\":\"Stark\", \"male\": true, \"children\": 7, \"weight\": 1.42}";

    BOOST_CHECK_EQUAL(parser.execute(str_dict), true);
    BOOST_REQUIRE_EQUAL(ast_ptr->exists(), true);

    xxon::Dict* dict = boost::get<xxon::Dict>(&ast_ptr->collection); 

    BOOST_REQUIRE(dict != NULL);
    BOOST_CHECK_EQUAL(dict->size(), 4);

    BOOST_CHECK_EQUAL(((*dict)["name"]).to<std::string>(), "Stark");
    BOOST_CHECK_EQUAL(((*dict)["male"]).to<bool>(), true);
    BOOST_CHECK_EQUAL(((*dict)["children"]).to<int>(), 7);
    BOOST_CHECK_CLOSE(((*dict)["weight"]).to<double>(), 1.42, 0.0001);
}

BOOST_AUTO_TEST_CASE(TestCaseParserJSON1)
{
    xxon::AST ast;
    xxon::Parser parser(ast);

    const std::string mywindow_str =
    "{ \
        \"title\": \"Hello World\", \
        \"position\": [ \
            200, \
            10 \
        ], \
        \"size\": [ \
            300, \
            400 \
        ], \
        \"border\": false \
    }";

    struct Window
    {
        std::string title;
        std::pair<double, double> position;
        std::pair<double, double> size;
        bool border;
    };

    Window window;

    BOOST_CHECK_EQUAL(parser.execute(mywindow_str), true);

    BOOST_REQUIRE_EQUAL(ast.exists(), true);
    BOOST_CHECK_EQUAL((ast["title"]).to<std::string>(), "Hello World");
    BOOST_CHECK_EQUAL((ast["border"]).to<bool>(), false);
    BOOST_CHECK_EQUAL((ast["position"][0]).to<int>(), 200);
    BOOST_CHECK_EQUAL((ast["position"][1]).to<int>(), 10);
    BOOST_CHECK_EQUAL((ast["size"][0]).to<int>(), 300);
    BOOST_CHECK_EQUAL((ast["size"][1]).to<int>(), 400);
}


BOOST_AUTO_TEST_CASE(TestCaseParserMediumSizeJSON)
{
    xxon::AST ast;
    xxon::Parser parser(ast);

    std::string empty_list = \
    "{ \
        \"health\": 64, \
        \"hosts\": [ \
            { \
                \"name\": \"Windows2000P\", \
                \"states\": [ \
                    { \
                        \"name\": \"CPU\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#CC99CC\" \
                    }, \
                    { \
                        \"name\": \"Disk\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#CC99CC\" \
                    }, \
                    { \
                        \"name\": \"Mem\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#CC99CC\" \
                    } \
                ] \
            }, \
            { \
                \"name\": \"Windows2003\", \
                \"states\": [ \
                    { \
                        \"name\": \"CPU\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#98FB98\" \
                    }, \
                    { \
                        \"name\": \"Disk\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#98FB98\" \
                    }, \
                    { \
                        \"name\": \"Mem\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#F08080\" \
                    } \
                ] \
            }, \
            { \
                \"name\": \"Windows7\", \
                \"states\": [ \
                    { \
                        \"name\": \"CPU\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#98FB98\" \
                    }, \
                    { \
                        \"name\": \"Disk\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#98FB98\" \
                    }, \
                    { \
                        \"name\": \"Mem\", \
                        \"link\": \"(html link)\", \
                        \"bgcolor\": \"#F08080\" \
                    } \
                ] \
            } \
        ] \
    }";

    auto result = parser.execute(empty_list);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(ast.exists(), true);

    BOOST_CHECK_EQUAL(ast["hosts"][0]["name"].to<std::string>(), "Windows2000P");
    BOOST_CHECK_EQUAL(ast["hosts"][1]["name"].to<std::string>(), "Windows2003");
    BOOST_CHECK_EQUAL(ast["hosts"][2]["name"].to<std::string>(), "Windows7");
}

BOOST_AUTO_TEST_CASE(TestCaseParserFile1)
{
    xxon::AST ast;
    xxon::Parser parser(ast);

    std::string str_list = "[1,true,false,4,\"Hello\"]";

    BOOST_CHECK_EQUAL(parser.execute_file("..\\test-suite\\data\\teste01.txt"), true);
    BOOST_REQUIRE_EQUAL(ast.exists(), true);
    
    BOOST_CHECK_EQUAL(ast["name"].to<std::string>(), "test-config-core");
    BOOST_CHECK_EQUAL(ast["plugin"]["plugins"][0]["type"].to<std::string>(), "text");
    BOOST_CHECK_EQUAL(ast["plugin"]["plugins"][1]["type"].to<std::string>(), "image");
}

BOOST_AUTO_TEST_SUITE_END();
