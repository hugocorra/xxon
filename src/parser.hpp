#ifndef XXON_PARSER_HPP
#define XXON_PARSER_HPP

#include "ast.hpp"
#include "definitions.hpp"

namespace xxon
{
    /* This class is responsible for load the AST tree with the contents
     * of a string or a file in the xxon format. 
     * TODO: create a wrapper to support an input stream directly.
     */
    class XXON_SPEC Parser
    {
    public:
        Parser(AST& ast);
        bool execute(const std::string& str);
        void reset(AST& ast);

    private:
        AST& _ast;
    };
};

#endif