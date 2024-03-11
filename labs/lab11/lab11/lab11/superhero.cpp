//
//  superhero.cpp
//  lab11
//
//  Created by Aditya Behal on 4/13/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "superhero.hpp"

using namespace std;

Superhero::Superhero(const string& nameIn, const string& identityIn, const string& powerIn) {
    name = nameIn;
    identity = identityIn;
    power = powerIn;
    good = true;
}

bool Superhero::operator== (const string& identityIn) const {
    return (identity == identityIn);
}

bool Superhero::operator!= (const string& identityIn) const {
    return !(identity == identityIn);
}

void Superhero::operator- () {
    if (isGood()) {
        good = false;
    } else {
        good = true;
    }
}

bool Superhero::operator> (const Superhero& hero) const {
    if (power == "Fire") {
        if (hero.power == "Wood") {
            return true;
        } else {
            return false;
        }
    } else if (power == "Wood") {
        if (hero.power == "Water") {
            return true;
        } else {
            return false;
        }
    } else if (power == "Water") {
        if (hero.power == "Fire") {
            return true;
        } else {
            return false;
        }
    } else {
        return (power < hero.power);
    }
}

ostream& operator<< (ostream& ostr, const Superhero& hero) {
    ostr << "Superhero " << hero.getName() << " has power " << hero.getPower() << endl;
    return ostr;
}
