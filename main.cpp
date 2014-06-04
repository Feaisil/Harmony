#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "core/engine.hpp"
#include "core/settings.hpp"

int main( int argc, char** argv)
{
    {
        std::ofstream logInit, logFinal;
        logInit.open ("initial.log");
        logFinal.open ("final.log");

        boost::archive::xml_oarchive arcInit(logInit), arcFinal(logFinal);
        //boost::archive::binary_oarchive arcInit(logInit), arcFinal(logFinal);

        harmony::core::Setting settings;
        settings.distanceFromStart = 2;
        settings.numberOfPlayers = 3;
        settings.isParallel = false;

        harmony::core::PlayerSetting playerSetting1;
        playerSetting1.name = "Fanny";
        playerSetting1.element = harmony::core::common::Element::Water;
        settings.playersSettings.push_back(playerSetting1);

        harmony::core::PlayerSetting playerSetting2;
        playerSetting2.name = "Paris";
        playerSetting2.element = harmony::core::common::Element::Fire;
        settings.playersSettings.push_back(playerSetting2);

        harmony::core::PlayerSetting playerSetting3;
        playerSetting3.name = "Blatte";
        playerSetting3.element = harmony::core::common::Element::Aether;
        settings.playersSettings.push_back(playerSetting3);

        harmony::core::Engine engine(settings);

        arcInit << BOOST_SERIALIZATION_NVP(engine);

        engine(100);

        arcFinal << BOOST_SERIALIZATION_NVP(engine);

        logInit.close();
        logFinal.close();
    }

    return 0;
}

