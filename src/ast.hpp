#ifndef XXON_AST_HPP
#define XXON_AST_HPP

#include <map>
#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/none.hpp>
#include <boost/variant/recursive_variant.hpp>

#include "definitions.hpp"

namespace xxon
{
    class AST;
    class Dict;
    class List;
    class AnyValueHolder;

    /* AnyValue can hold any type supported by JSON. */
    typedef boost::variant<
        boost::blank,
        Dict,
        List,
        bool,
        int,
        double,
        std::string
    > AnyValue;

    /* Dict is a structure that associates keys with values. The key should be a 
     * string and the value can be any type supported by AnyValue. */
    class XXON_SPEC Dict {
    public:
        typedef std::map<std::string, xxon::AnyValueHolder> NodeType;

        Dict() : items() {};

        AnyValueHolder& operator[](const std::string& key);

        size_t size() const { return items.size(); }
        NodeType items;
    };

    /* List represents a sequentially heterogeneous container, that holds any
     * type supported by AnyValue. */
    class XXON_SPEC List {
    public:
        typedef std::vector<xxon::AnyValueHolder> NodeType;

        List() : values(0) {};

        AnyValueHolder& operator[](size_t index);

        size_t size() const { return values.size(); }
        NodeType values;
    };

    class XXON_SPEC AnyValueHolder
    {
    public:
        typedef AnyValue NodeType;
        AnyValueHolder(xxon::AnyValue& any__value) : any_value(any__value) {};
        AnyValueHolder() : any_value() {};

        AnyValueHolder& operator[](const std::string& key);
        AnyValueHolder& operator[](size_t index);

        template <typename T>
        T& to(){
            T* t_value = boost::get<T>(&any_value);

            if (t_value)
                return *t_value;

            throw "error 345678";
        }


        xxon::AnyValue any_value;
    };

    /* AST is a structure that holds one of three types of information:
     *  0 - Nothing, there's no tree.
     *  1 - Dict, the root node is a dict.
     *  2 - List, the root node is a list. */
    class XXON_SPEC AST {
    public:
        AST() : collection(boost::none) {};

        AnyValueHolder& operator[](const std::string& key);
        AnyValueHolder& operator[](size_t index);
        bool exists() const { return collection.which() != 0; }

        typedef boost::variant<boost::none_t, Dict, List> NodeType;
        NodeType collection;
    };
};

/* in order to use some spirit features, it's necessary to transform all 
 * structures into random access sequences. */
BOOST_FUSION_ADAPT_STRUCT(
    xxon::AST,
    (xxon::AST::NodeType, collection)
)

BOOST_FUSION_ADAPT_STRUCT(
    xxon::List,
    (xxon::List::NodeType, values)
)

BOOST_FUSION_ADAPT_STRUCT(
    xxon::Dict,
    (xxon::Dict::NodeType, items)
)

BOOST_FUSION_ADAPT_STRUCT(
    xxon::AnyValueHolder,
    (xxon::AnyValueHolder::NodeType, any_value)
)

#endif


