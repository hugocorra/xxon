//#ifndef XXON_HANDLER_HPP
//#define XXON_HANDLER_HPP
//
//#include <boost/variant/static_visitor.hpp>
//
//#include "ast.hpp"
//#include "definitions.hpp"
//
//namespace xxon
//{
//    class collectionSize : public boost::static_visitor<size_t>
//    {
//    public:
//        template <typename T> size_t operator()(T &t) const
//        {
//            return static_cast<size_t>(0);
//        }
//
//        size_t operator()(xxon::Dict& dict) const
//        {
//            return dict.size();
//        }
//    
//        size_t operator()(xxon::List& list) const
//        {
//            return list.size();
//        }
//    };
//
//    template <typename T>
//    void getDictValue(const xxon::Dict* dict, const std::string& key, T& variable)
//    {
//        auto it = dict->items.find(key);
//
//        if (it != dict->items.end())
//        {
//            const T* value_ptr = boost::get<T>(&(it->second));
//
//            if (value_ptr != NULL)
//                variable = *value_ptr;
//        }
//    }
//
//    template <typename ContainerType>
//    bool fillContainer(xxon::List& lst, ContainerType& container)
//    {
//        for (auto it = lst.values.begin(); it != lst.values.end(); ++it)
//        {
//            ContainerType::value_type *t_value = boost::get<T>(&(*it));
//            if (t_value)
//                container.push_back(t_value);
//        }
//    }
//
//    //struct Getter{
//    //    Getter(xxon::Dict& dict) : _dict(dict) {};
//
//    //    Getter operator[](const std::string& key)
//    //    {
//    //        auto it = _dict->items.find(key);
//
//    //        if (it != dict->items.end())
//    //        {
//    //            const T* value_ptr = boost::get<T>(&(it->second));
//
//    //        }
//
//
//    //    xxon::Dict& _dict;
//    //};
//
//};
//
//#endif
