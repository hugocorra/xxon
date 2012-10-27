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

    /* basically, there are only four important chars that the parse needs to 
     * find an take an action: ":" "," "{" and "}". */
    template <typename Iterator, typename Skipper = ascii::space_type>
    struct Grammar : qi::grammar<Iterator, AST(), Skipper>
    {
        Grammar() : Grammar::base_type(astx)
        {
            using qi::lit;
            using qi::lexeme;
            using ascii::char_;
            using ascii::string;
            using namespace qi::labels;

            using phoenix::at_c;
            using phoenix::insert;
			using phoenix::push_back;

			//using phoenix::push_back_a;
            
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

            //key   =  lexeme[+(char_ - ':')[_val += _1]];

			//any_value = qi::int_;

			//qi::longest_alternative[ integer | real ];

			text = '"' >> lexeme[+(char_ - '"')        [_val += _1]] >> '"';

            key   =  '"' >> lexeme[+(char_ - '"')[_val += _1]] >> '"'; //< reads everything until a : character.
            
            value =  (text | qi::bool_ | qi::double_ | dict | list); //qi::int_; //lexeme[+(char_ - '<')        [_val += _1]];
			
			
            pair  = 
				key                          //< apply key rule
				>>  -(':' >> value ); //< reads the : not consumed by the key rule, then
                                      //  reads a pair of key,value (<string, string>),
                                      //  or a pair of key,value (<string, AST>).

			dict = lit('{')
				>>  pair[insert(at_c<0>(_val), _1)] % ','
				>> lit('}');


			list = lit('[')
				>> (qi::bool_ | qi::double_ | text | dict)[push_back(at_c<0>(_val), qi::_1)] % ','
				>> lit(']');

			astx = dict[push_back(at_c<0>(_val), qi::_1)]; //list[push_back(at_c<0>(_val), qi::_1)];
        }

        qi::rule<Iterator, AST(),         Skipper> astx;
		qi::rule<Iterator, List(),        Skipper> list;
		qi::rule<Iterator, Dict(),        Skipper> dict;

		qi::rule<Iterator, std::pair<std::string, AnyValue>(), Skipper> pair;

		qi::rule<Iterator, std::string(), Skipper> key;
		qi::rule<Iterator, AnyValue(),    Skipper> value;
		qi::rule<Iterator, std::string(), Skipper> text;

  //      qi::rule<Iterator, bool(),        Skipper> value_bool;
  //      qi::rule<Iterator, double(),      Skipper> value_double;
		//qi::rule<Iterator, int(),         Skipper> value_int;
  //      qi::rule<Iterator, std::string(), Skipper> value_str;

		//qi::rule<Iterator, AnyValue, Skipper> any_value;
		//qi::rule<Iterator, std::string(), Skipper> key;
    };
};

#endif

