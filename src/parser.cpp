#include <iterator>
#include <stdexcept>
#include <string>

#include <boost/spirit/include/qi.hpp>

#include "ast.hpp"
#include "ast_debugger.hpp"
#include "grammar.hpp"
#include "parser.hpp"

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace xxon
{
    Parser::Parser(AST& ast) :
        _ast(ast)
    {
    }

    bool Parser::execute(const std::string& str)
    {      
        if (str.empty())
            return true;

		using boost::spirit::ascii::space;

        //auto skipper =  ascii::space | '#' >> *(qi::char_ - qi::eol) >> qi::eol;
        //typedef decltype(skipper) skipper_type;
        
        Grammar<std::string::const_iterator> gramar;

        std::string::const_iterator iter = str.begin();
		std::string::const_iterator end = str.end();

		//std::cout << "test..." << std::endl;
		//std::cout << "vector size = " << _ast.nodes.size() << std::endl;

		bool r = boost::spirit::qi::phrase_parse(iter, end, gramar, space, _ast);
        return r && (iter == str.end());
    }

    void Parser::reset(AST& ast)
    {
        _ast = ast;
    }
}

