#include <map>
#include <boost/variant.hpp>

#include "ast.hpp"

namespace xxon
{
    AnyValueHolder& Dict::operator[](const std::string& key)
    {
        auto entry = items.find(key);
                
        if (entry != items.end())
            return entry->second;

        throw("error #21319o9");
    }

    AnyValueHolder& List::operator[](size_t index)
    {
        return values[index];
    }

    AnyValueHolder& AnyValueHolder::operator[](const std::string& key)
    {
        xxon::Dict* dict = boost::get<xxon::Dict>(&any_value);

        if (dict)
        {
            auto entry = dict->items.find(key);
                
            if (entry != dict->items.end())
                return entry->second;
        }

        throw "error #4321321";
    };

    AnyValueHolder& AnyValueHolder::operator[](size_t index)
    {
        xxon::List* list = boost::get<xxon::List>(&any_value);
        
        if (list)
        {
            return list->values[index];
        }

        throw "list error #ed92i193";
    }

    AnyValueHolder& AST::operator[](const std::string& key)
    {
        xxon::Dict* dict = boost::get<xxon::Dict>(&collection);

        if (dict)
        {
            auto entry = dict->items.find(key);
                
            if (entry != dict->items.end())
                return entry->second;
        }

        throw "error #451233488";

    }

    AnyValueHolder& AST::operator[](size_t index)
    {
        xxon::List* list = boost::get<xxon::List>(&collection);
        
        if (list)
        {
            return list->values[index];
        }

        throw "list error #ed92i193";
    }
}
