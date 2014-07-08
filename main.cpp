#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "core/engine.hpp"
#include "core/settings.hpp"
#include "interface/commandlineinterface.hpp"

int main( int argc, char** argv)
{
    {
        std::ofstream logInit, logFinal;
        logInit.open ("initial.log");
        logFinal.open ("final.log");

        boost::archive::xml_oarchive arcInit(logInit), arcFinal(logFinal);
        //boost::archive::binary_oarchive arcInit(logInit), arcFinal(logFinal);

        boost::shared_ptr<harmony::interface::CommandLineInterface> interface(new harmony::interface::CommandLineInterface());

        (*interface)();

        harmony::core::Engine engine(interface->settings);

        arcInit << BOOST_SERIALIZATION_NVP(engine);

        engine(5);

        arcFinal << BOOST_SERIALIZATION_NVP(engine);

        logInit.close();
        logFinal.close();
    }

    return 0;
}

