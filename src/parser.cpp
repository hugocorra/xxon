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
            throw(std::invalid_argument("[error]: parcer received an invalid argument!"));

        auto skipper =  ascii::space | '#' >> *(qi::char_ - qi::eol) >> qi::eol;
        typedef decltype(skipper) skipper_type;
        
        Grammar<std::string::const_iterator, skipper_type> gramar;

        auto iter = str.begin();

		//std::cout << "test..." << std::endl;
		//std::cout << "vector size = " << _ast.nodes.size() << std::endl;

		AST x;
		bool r = boost::spirit::qi::phrase_parse(iter, str.end(), gramar, skipper, x);       

		_ast = x;

        return r && (iter == str.end());
    }

    void Parser::reset(AST& ast)
    {
        _ast = ast;
    }
}

