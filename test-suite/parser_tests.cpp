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
    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
    xxon::Parser parser(*ast_ptr);

	std::string str_list = "[1,true,false,4,\"Hello\"]";

	BOOST_CHECK_EQUAL(parser.execute_file("..\\test-suite\\data\\teste01.txt"), true);
	BOOST_REQUIRE_EQUAL(ast_ptr->exists(), true);
}


/**
 * Test Description: Test the parser behavior with empty strings.
 **/
//BOOST_AUTO_TEST_CASE(TestCaseParserEmpty)
//{
//    boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
//    xxon::Parser parser(*ast_ptr);
//
//    std::string empty_1 = "";
//    std::string empty_2 = "#this is a commentary";
//
//    // parser should throw an exception, in case of an empty string.
//    BOOST_REQUIRE_THROW(parser.execute(empty_1), std::invalid_argument);
//
//    // parser should return true, in case of a string with only commentaries.
//    BOOST_CHECK_EQUAL(parser.execute(empty_2), true);
//}

//BOOST_AUTO_TEST_CASE(TestCaseParserEmptyDict)
//{
 //   boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
 //   xxon::Parser parser(*ast_ptr);

	//std::string empty_dict = "{}";

 //   // parser should throw an exception, in case of an empty string.
 //   parser.execute(empty_dict);

	//std::cout << "DictTest Size = " << ast_ptr->nodes.size() << std::endl;

    // parser should return true, in case of a string with only commentaries.
    //BOOST_CHECK_EQUAL(parser.execute(empty_2), true);
//}

//BOOST_AUTO_TEST_CASE(TestCaseParserEmptyListXXXX)
//{
//    //boost::shared_ptr<xxon::AST> ast_ptr(new xxon::AST);
//	xxon::AST a;
//    xxon::Parser parser(a);
//
////	std::string empty_list = "[77, 88.1, true, 5, false, 1]";
//	
//	//std::string empty_list = "{\"idade\": 10}";
//
//
//	//std::string empty_list = "\
//	//{\
//	//	\"nome\": \"hugo\",\
//	//	\"idade\": 28,\
//	//	\"cores\": [\
//	//		\"azul\",\
//	//		\"verde\",\
//	//		\"amarelo\"\
//	//	],\
//	//	\"endereco\": {\
//	//		\"cidade\": \"Sao Jose\",\
//	//		\"rua\": \"Quintana\",\
//	//		\"numero\": 915\
//	//	},\
//	//	\"computadores\": [\
//	//		{\
//	//			\"cpmp\": \"endevour\"\
//	//		},\
//	//		{\
//	//			\"comp\": \"columbia\"\
//	//		}\
//	//	]\
//	//}";
//
//	std::string empty_list = \
//"{ \
//    \"health\": 64, \
//    \"hosts\": [ \
//        { \
//            \"name\": \"Windows2000P\", \
//            \"states\": [ \
//                { \
//                    \"name\": \"CPU\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#CC99CC\" \
//                }, \
//                { \
//                    \"name\": \"Disk\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#CC99CC\" \
//                }, \
//                { \
//                    \"name\": \"Mem\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#CC99CC\" \
//                } \
//            ] \
//        }, \
//        { \
//            \"name\": \"Windows2003\", \
//            \"states\": [ \
//                { \
//                    \"name\": \"CPU\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#98FB98\" \
//                }, \
//                { \
//                    \"name\": \"Disk\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#98FB98\" \
//                }, \
//                { \
//                    \"name\": \"Mem\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#F08080\" \
//                } \
//            ] \
//        }, \
//        { \
//            \"name\": \"Windows7\", \
//            \"states\": [ \
//                { \
//                    \"name\": \"CPU\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#98FB98\" \
//                }, \
//                { \
//                    \"name\": \"Disk\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#98FB98\" \
//                }, \
//                { \
//                    \"name\": \"Mem\", \
//                    \"link\": \"(html link)\", \
//                    \"bgcolor\": \"#F08080\" \
//                } \
//            ] \
//        } \
//    ] \
//}";
//
//    // parser should throw an exception, in case of an empty string.
//	std::cout << "parsing...." << std::endl;
//    parser.execute(empty_list);
//	std::cout << "fim parsing...." << std::endl;
//
//	//std::cout << "ListTest Size = " << a.nodes.size() << std::endl;
//	//std::copy(ast_ptr->nodes.begin(), ast_ptr->nodes.end(), std::ostream_iterator<int>(std::cout, ";"));
//	//std::cout << std::endl;
//
//	//debug_ast(a);
//
//    // parser should return true, in case of a string with only commentaries.
//    //BOOST_CHECK_EQUAL(parser.execute(empty_2), true);
//}

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
