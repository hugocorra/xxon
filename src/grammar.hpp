#ifndef XXON_GRAMMAR_HPP
#define XXON_GRAMMAR_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_directive.hpp>
//#include <boost/phoenix/stl/container.hpp>
#include <boost/spirit/home/classic/core/composite/directives.hpp>
#include <boost/typeof/typeof.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "ast.hpp"

namespace xxon
{
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    template <typename Iterator, typename Skipper = ascii::space_type>
    struct Grammar : public qi::grammar<Iterator, AST(), Skipper>
    {
        Grammar() : Grammar::base_type(ast)
        {
            using ascii::char_;

            using phoenix::at_c;
            using phoenix::insert;
            using phoenix::push_back;

            using qi::bool_;
            using qi::double_;
            using qi::lexeme;
            using qi::lit;
            using qi::eps;

            using namespace qi::labels;

			text = '"' 
				>> lexeme[+(char_ - '"')[_val += _1]]
				>> '"';

            key   =  '"' 
				>> lexeme[+(char_ - '"')[_val += _1]]
				>> '"';
            
            value =  (text | bool_ | double_ | dict | list);
		
            pair  = key               
				>>  -(':' >> value ); //< reads the : not consumed by the key rule, then...

			dict = lit('{')
				>> *(pair[insert(at_c<0>(_val), _1)] % ',')
				>> lit('}');

			list = lit('[')
				>> *(value[push_back(at_c<0>(_val), qi::_1)] % ',')
				>> lit(']');

			ast = dict[at_c<0>(_val) = _1] | list[at_c<0>(_val) = _1] | eps;
        }

        qi::rule<Iterator, AnyValue(),    Skipper> value;
        qi::rule<Iterator, AST(),         Skipper> ast;
        qi::rule<Iterator, Dict(),        Skipper> dict;
        qi::rule<Iterator, List(),        Skipper> list;
        qi::rule<Iterator, std::pair<std::string, AnyValue>(), Skipper> pair;
        qi::rule<Iterator, std::string(), Skipper> key;
        qi::rule<Iterator, std::string(), Skipper> text;
    };
};

#endif

