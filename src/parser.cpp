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

    void Parser::reset(AST& ast)
    {
        _ast = ast;
    }
}

