/*
  OptionsMenuData.hpp
  Author : Cyrion
  File under GNU GPL v3.0 license
*/
#pragma once

#include "UiData.hpp"

namespace OpMon {
    namespace Model {

        class OptionsMenuData {
          private:
            UiData *uidata;
            sf::Texture background;
            sf::Texture selectBar;
            sf::Texture langBg;
            sf::Texture yesTx;
            sf::Texture creditsBg;
            sf::Texture volumeCur;

            OptionsMenuData(OptionsMenuData const &);

          public:
            sf::Texture const &getBackground() const { return background; }
            sf::Texture const &getSelectBar() const { return selectBar; }
            sf::Texture const &getLangBg() const { return langBg; }
            sf::Texture const &getYesTx() const { return yesTx; }
            sf::Texture const &getCreditsBg() const { return creditsBg; }
            sf::Texture const &getVolumeCur() const { return volumeCur; }
            UiData *getUiDataPtr() { return uidata; }
            OptionsMenuData(UiData *data);
        };
    } // namespace Model
} // namespace OpMon
