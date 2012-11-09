#ifndef XXON_AST_HPP
#define XXON_AST_HPP

#include <map>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace xxon
{
    class AST;
    class Dict;
    class List;

	/* AnyValue can hold any type supported by JSON. */
    typedef boost::variant<
        boost::none_t,
		Dict,
		List,
		bool,
        int,
		double,
		std::string
    > AnyValue;

	/* Dict is a structure that associates keys with values. The key should be a 
	 * string and the value can be any type supported by AnyValue. */
    class Dict {
	public:
        typedef std::map<std::string, AnyValue> NodeType;

		Dict() : items() {};
        size_t size() const { return items.size(); }
        NodeType items;
    };

	/* List represents a sequentially heterogeneous container, that holds any
	 * type supported by AnyValue. */
    class List {
	public:
        typedef std::vector<AnyValue> NodeType;

		List() : values(0) {};
        size_t size() const { return values.size(); }
        NodeType values;
    };

	/* AST is a structure that holds one of three types of information:
	 *  0 - Nothing, there's no tree.
	 *  1 - Dict, the root node is a dict.
	 *  2 - List, the root node is a list. */
    class AST {
	public:
		AST() : collection(boost::none) {};

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

#endif


