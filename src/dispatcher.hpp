//#ifndef XXON_DISPATCHER_HPP
//#define XXON_DISPATCHER_HPP
//
//#include <map>
//#include <boost/function.hpp>
//
//#include "ast.hpp"
//#include "definitions.hpp"
//
//namespace xxon
//{
//    /* this class is used to connect AST properties (pair<string, AST>)
//     * to callbacks that can handle the AST node. */
//    class XXON_SPEC Dispatcher
//    {
//    public:
//        typedef boost::function<bool (AST&)> FunctionAST;
//
//        /* callbacks execution */
//        size_t operator()(AST& ast);
//
//        /* register a function, needs the property key and the callback */
//        void registerAST(const std::string& name, FunctionAST func);
//
//    private:
//        std::multimap<std::string, FunctionAST> _vec_functions_ast;
//    };
//};
//
//#endif
//
//
