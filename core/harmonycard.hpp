#pragma once

#include <boost/serialization/nvp.hpp>

namespace harmony{ namespace core{


class HarmonyCard
{
public:
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
    }
};

}}
