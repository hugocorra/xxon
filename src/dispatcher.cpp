//#include <boost/variant.hpp>
//#include "dispatcher.hpp"
//
//namespace xxon
//{
//    size_t Dispatcher::operator()(AST& ast)
//    {
//        size_t counter = 0;
//
//        for (auto it = _vec_functions_ast.begin(); it != _vec_functions_ast.end(); ++it)
//        {
//            auto ast_key = ast.properties.find(it->first);
//            if (ast_key == ast.properties.end())
//                continue;
//
//            if (AST* ast_node = boost::get<AST>(&ast_key->second))
//            {
//                it->second(*ast_node);
//                ++counter;
//            }
//        }
//
//        return counter;
//    }
//
//    void Dispatcher::registerAST(const std::string& name, FunctionAST func)
//    {
//        _vec_functions_ast.insert(make_pair(name, func));
//    }
//}
