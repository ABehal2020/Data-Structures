//
//  superhero.hpp
//  lab11
//
//  Created by Aditya Behal on 4/13/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef superhero_hpp
#define superhero_hpp

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Superhero {
public:
    Superhero(const string& nameIn, const string& identityIn, const string& powerIn);
    const string& getName() const { return name; }
    const string& getPower() const { return power; }
    bool isGood() const { return good; }
    bool operator== (const string& identityIn) const;
    bool operator!= (const string& identityIn) const;
    void operator- ();
    bool operator> (const Superhero& hero) const;
    friend class Team;
private:
    const string& getTrueIdentity() const { return identity; };
    string name;
    string identity;
    string power;
    bool good;
};

ostream& operator<< (ostream& ostr, const Superhero& hero);

#endif /* superhero_hpp */
