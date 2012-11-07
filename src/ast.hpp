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

    typedef boost::variant<
        boost::none_t,
		Dict,
		List,
		bool,
        int,
		double,
		std::string
    > AnyValue;

    class Dict {
	public:
        typedef std::map<std::string, AnyValue> NodeType;

		Dict() : items() {};
        size_t size() const { return items.size(); }
        NodeType items;
    };

    class List {
	public:
        typedef std::vector<AnyValue> NodeType;

		List() : values(0) {};
        size_t size() const { return values.size(); }
        NodeType values;
    };

    class AST {
	public:
		AST() : collection(boost::none) {};

        bool exists() const { return collection.which() != 0; }

        typedef boost::variant<boost::none_t, Dict, List> NodeType;
		NodeType collection;
    };
};

/* in order to use some spirit features, it's necessary to transform it in a random access sequence. */
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


