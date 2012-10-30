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
		Dict,
		List,
		bool,
		double,
		std::string
    > AnyValue;

    class Dict {
	public:
		Dict() : items() {};

		typedef std::map<std::string, AnyValue> NodeType;
        NodeType items;
    };

    class List {
	public:
		List() : values(0) {};

		typedef std::vector<AnyValue> NodeType;
		//typedef std::vector<std::string> NodeType;
		//typedef int NodeType;
		//typedef std::vector<int> NodeType;
        NodeType values;
    };

    class AST {
	public:
		AST() : collection(boost::none) {};
		//AST() : nodes(0) {};

		//typedef std::vector<boost::variant<Dict, List>> NodeType;
		//typedef std::vector<int> NodeType;
        //NodeType nodes;
		typedef boost::variant<boost::none_t, Dict, List> NodeType;
		NodeType collection;
    };

    /* a tree node can be: <string, string> or <string, AST> */
    //typedef std::map<std::string, ASTNode> NodeType;
    
    //class AST;
    //
    ///* recursive wrapper, works like a tree */
    //typedef boost::variant<
    //    boost::recursive_wrapper<AST>,
    //    std::string
    //> ASTNode;
    //
    ///* a tree node can be: <string, string> or <string, AST> */
    //typedef std::map<std::string, ASTNode> NodeType;
    //
    //class AST
    //{
    //public:
    //    /* this function is responsible to get the value of a pair<string, string>,
    //     * inside the map properties. 
    //     * TODO: I really don't like this method here! In the future, it should be moved inside
    //     *       the Dispatcher and should work as a lazy function. */
    //    template <typename T>
    //    bool getDirective(const std::string& name, T& value_typed)
    //    {
    //        try
    //        {
    //            auto it = properties.find(name);
    //            if (it != properties.end())
    //            {
    //                // check the value type, and convert it to type T.
    //                if (std::string* is_string = boost::get<std::string>(&it->second))
    //                    value_typed = boost::lexical_cast<T>(*is_string);
    //            }
    //        }
    //        catch(boost::bad_lexical_cast &)
    //        {
    //            return false;
    //        }

    //        return true;
    //    }

    //    NodeType properties;
    //};
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


