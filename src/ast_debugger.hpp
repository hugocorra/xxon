//#ifndef XXON_AST_DEBUGGER_HPP
//#define XXON_AST_DEBUGGER_HPP
//
//#include <boost/variant/static_visitor.hpp>
//#include "ast.hpp"
//
//namespace xxon
//{
//    /* the following class is a visitor of two variant types (string and AST),
//     * and it prints all tree nodes. It puts some \t before the key/value, in order
//     * to show the nodes hierarchy. */
//    class ast_visitor : public boost::static_visitor<>
//    {
//    public:
//        ast_visitor(size_t level = 0) :
//          _level(level)
//        {
//        }
//
//        void operator()(AST &i) const
//        {
//            std::string tabulator(_level, '\t');
//
//            std::cout << "[VISITION SUBTREE, SIZE = " <<  i.properties.size() << "]" << std::endl;
//            for (auto it = i.properties.begin(); it != i.properties.end(); ++it)
//            {
//                std::cout << tabulator << "> key: " << it->first << "\t";
//                boost::apply_visitor( ast_visitor(_level+1), it->second);
//                std::cout << std::endl;
//            }
//        }
//
//        void operator()(std::string & str) const
//        {
//            std::cout <<  "value: " << str;
//        }
//    
//    private:
//        size_t _level;
//    };
//    
//    /* prints the whole tree structure. */
//    void debug_ast(AST& ast)
//    {
//        for (auto it = ast.properties.begin(); it != ast.properties.end(); ++it)
//        {
//            std::cout << "> key: " << it->first << "\t";
//            boost::apply_visitor(ast_visitor(1), it->second);
//            std::cout << std::endl;
//        }
//    }
//};
//
//#endif
//
//
