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

        template <typename TStream>
        bool execute(const TStream& stream) //(const std::string& str);
        {
		    using boost::spirit::ascii::space;

            //auto skipper =  ascii::space | '#' >> *(qi::char_ - qi::eol) >> qi::eol;
            //typedef decltype(skipper) skipper_type;
        
            Grammar<TStream::const_iterator> gramar;

            TStream::const_iterator iter = stream.begin();
		    TStream::const_iterator end = stream.end();

		    bool r = boost::spirit::qi::phrase_parse(iter, end, gramar, space, _ast);
            return r && (iter == stream.end());
        }

        void reset(AST& ast);

    private:
        AST& _ast;
    };
};

#endif