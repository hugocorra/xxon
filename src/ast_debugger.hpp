#ifndef XXON_AST_DEBUGGER_HPP
#define XXON_AST_DEBUGGER_HPP

#include <typeinfo>
#include <boost/variant/static_visitor.hpp>
#include "ast.hpp"

namespace xxon
{
    /* the following class is a visitor of two variant types (string and AST),
     * and it prints all tree nodes. It puts some \t before the key/value, in order
     * to show the nodes hierarchy. */
    class ast_visitor : public boost::static_visitor<>
    {
    public:
        ast_visitor(size_t level = 0) :
          _level(level),
		  _tabs(level, '\t')
        {
        }

        void operator()(AST &i) const
        {
            std::string tabulator(_level, '\t');

            std::cout << "[VISITION SUBTREE, SIZE = " <<  i.nodes.size() << "]" << std::endl;
            for (auto it = i.nodes.begin(); it != i.nodes.end(); ++it)
            {
                //std::cout << tabulator << "> key: " << it->first << "\t";
                //boost::apply_visitor(ast_visitor(_level+1), it);
                //std::cout << std::endl;
            }
        }

		void operator()(List& l) const
		{
			std::cout <<  _tabs << "list: " << l.values.size() << std::endl;
			for (auto it = l.values.begin(); it != l.values.end(); ++it)
			{
				boost::apply_visitor(ast_visitor(_level+1), *it);
			}
		}

	
		void operator()(Dict& d) const
		{
			std::cout <<  _tabs << "dict: " << d.items.size() << std::endl;
			for (auto it = d.items.begin(); it != d.items.end(); ++it)
			{
				for (size_t i = 0; i < _level; ++i)
					std::cout << "\t";

				std::cout << it->first << ":" << std::endl;
				boost::apply_visitor(ast_visitor(_level+1), it->second);
			}
		}

		void operator()(int& t) const
		{
			std::cout << _tabs << "int: " << t << std::endl;
		}

		void operator()(double& t) const
		{
			std::cout << _tabs << "double: " << t << std::endl;
		}

		void operator()(bool& t) const
		{
			std::cout << _tabs << "bool: " << t << std::endl;
		}

		//void operator()(std::string &str)
		//{
		//	std::cout << "[d] string: " << str << std::endl;
		//}

		void operator()(std::string& t) const
		{
			std::cout << _tabs << "string: " << t << std::endl;
		}

		void operator()(char &c)
		{
			std::cout << _tabs << "char: " << c << std::endl;
		}

		template <typename T>
		void operator()(T& t) const
		{
			
			std::cout << _tabs << "generic!!" << typeid(T).name() << std::endl;
		}

		//void operator()(AST::NodeType l) const
		//{
		//	std::cout <<  "[d] list: " << std::endl;
		//}

		//void operator()(int l) const
		//{
		//	std::cout <<  "[d] int: " << std::endl;
		//}


		//void operator()(double l) const
		//{
		//	std::cout <<  "[d] double: " << std::endl;
		//}

  //      void operator()(std::string & str) const
  //      {
  //          std::cout <<  "[d] value: " << str;
  //      }
    
    private:
		std::string _tabs;
        size_t _level;
    };
    
    /* prints the whole tree structure. */
    void debug_ast(AST& ast)
    {
        for (auto it = ast.nodes.begin(); it != ast.nodes.end(); ++it)
        {
            //std::cout << "> key: " << it-> << "\t";
			//std::cout << "[d] traversing node: " << std::endl;
			boost::apply_visitor(ast_visitor(1), *it);
            //std::cout << std::endl;
        }
    }
};

#endif


