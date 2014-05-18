#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "core/engine.hpp"

int main( int argc, char** argv)
{
    {
        std::ofstream logInit, logFinal;
        logInit.open ("initial.log");
        logFinal.open ("final.log");

        boost::archive::xml_oarchive arcInit(logInit), arcFinal(logFinal);

        harmony::core::Engine engine;

        arcInit << BOOST_SERIALIZATION_NVP(engine);

        engine(10);

        arcFinal << BOOST_SERIALIZATION_NVP(engine);

        logInit.close();
        logFinal.close();
    }

    return 0;
}

