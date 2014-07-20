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

        boost::shared_ptr<harmony::core::Engine> engine(new harmony::core::Engine(interface->settings));
        interface->engine = engine;

        arcInit << boost::serialization::make_nvp(BOOST_PP_STRINGIZE(engine), *engine);

        (*engine)(5);

        arcFinal << boost::serialization::make_nvp(BOOST_PP_STRINGIZE(engine), *engine);

        logInit.close();
        logFinal.close();
    }

    return 0;
}

