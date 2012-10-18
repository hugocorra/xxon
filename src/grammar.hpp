#ifndef XXON_GRAMMAR_HPP
#define XXON_GRAMMAR_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
//#include <boost/phoenix/stl/container.hpp>
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

    /* basically, there are only four important chars that the parse needs to 
     * find an take an action: ":" "," "{" and "}". */
    template <typename Iterator, typename Skipper = ascii::space_type>
    struct Grammar : qi::grammar<Iterator, AST(), Skipper>
    {
        Grammar() : Grammar::base_type(ast)
        {
            using qi::lit;
            using qi::lexeme;
            using ascii::char_;
            using ascii::string;
            using namespace qi::labels;

            using phoenix::at_c;
            using phoenix::insert;
			using phoenix::push_back;
            
        //    key   =  
        //        !lit('}')                           //< ignore any sequence starting with }
        //    >>  lexeme[+(char_ - ':')[_val += _1]]; //< reads everything until a : character.
        //    
        //    value = 
        //        !lit('{')                           //< ignore any sequence starting with {
        //    >>  lexeme[+(char_ - ',')[_val += _1]]; //< reads everything until a , character.
        //    
        //    pair  = 
        //        !lit('}')                    //< ignore any sequence starting with }
        //    >>  key                          //< apply key rule
        //    >>  -(':' >> value | ast_child); //< reads the : not consumed by the key rule, then
        //                                     //  reads a pair of key,value (<string, string>),
        //                                     //  or a pair of key,value (<string, AST>).

        //    ast_child %=
        //        lit(':')                         //< only sequences starting with : character.
        //    >>  lit('{')                         //< only sequences followed by a { character.
        //    >>  *(-(qi::lit(','))                //< ignores , character
        //    >>  pair[insert(at_c<0>(_val), _1)]) //< apply the pair rule, and puts the value inside the AST.
        //    >>  -(lit(','))                      //< the sequence should have a , character before the end.
        //    >>  lit('}');                        //< the child sequence should be closed by a } character.
        //    
        //    ast %= 
        //        pair[insert(at_c<0>(_val), _1)]       //< reads a pair 
        //    >>  *(qi::lit(',')                        //< reads a list of pairs, separated by , character.
        //    >>  pair[insert(at_c<0>(_val), _1)]); //< notice that the setence was started in the line abouve.
        //} 

        //qi::rule<Iterator, AST(), Skipper> ast;
        //qi::rule<Iterator, AST(), Skipper> ast_child;
        //qi::rule<Iterator, std::pair<std::string, ASTNode>(), Skipper> pair;
        //qi::rule<Iterator, std::string(), Skipper> key, value;

            ///*****************************************************************///

			using qi::int_;

			 //list[phoenix::push_back(at_c<0>(_val))];



			//push_back(at_c<0>, 10);


			//list =
			//	!lit('}')                               //< ignore any sequence starting with }
			//	>>  lexeme[+(char_ - ':')[_val += _1]]; //< reads everything until a : character.

			//ast %= 
			//	list[push_back(at_c<0>(_val), _1)]; 

			//ast %= value_int[push_back(at_c<0>, 10)];

			//value_str = lexeme[+(char_ - '"')        [_val += _1]];

			
			//ast = value_str;
        }

        qi::rule<Iterator, AST(),         Skipper> ast;
		qi::rule<Iterator, List(),        Skipper> list;

        qi::rule<Iterator, bool(),        Skipper> value_bool;
        qi::rule<Iterator, double(),      Skipper> value_double;
		qi::rule<Iterator, int(),         Skipper> value_int;
        qi::rule<Iterator, std::string(), Skipper> value_str;
    };
};

#endif

