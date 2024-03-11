//
//  team.cpp
//  lab11
//
//  Created by Aditya Behal on 4/14/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <cassert>
#include "superhero.hpp"
#include "team.hpp"

bool isvowel(char c) {
    if (!isalpha(c)) return false;
    char c2 = tolower(c);
    return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
    return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
    if (superheroes.size() == 0)
        return "";
    std::string answer;
    std::list<Superhero>::const_iterator itr;
    for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
        char first_consonant = ' ';
        char first_vowel = ' ';
        std::string true_identity = itr->getTrueIdentity();
        for (int j = 0; j < true_identity.size(); j++) {
            if (first_consonant == ' ' && isconsonant(true_identity[j]))
                first_consonant = tolower(true_identity[j]);
            if (first_vowel == ' ' && isvowel(true_identity[j]))
                first_vowel = tolower(true_identity[j]);
        }
        answer.push_back(first_consonant);
        answer.push_back(first_vowel);
    }
    
    answer[0] = toupper(answer[0]);
    return answer;
}

/*
 This name is automatically formed by taking the first consonant of the
 first team member’s true identity, the first vowel of the first team member’s true identity, the first consonant
 of the second team member’s true identity, the first vowel of the second team member’s true identity, etc.
 You will need to add a friend relationship to compile this code
 */

void Team::operator+=(const Superhero &a) {
    superheroes.push_back(a);
}

void Team::operator-=(const Superhero &a) {
    for (list<Superhero>::iterator itr = superheroes.begin(); itr != superheroes.end(); itr++) {
        if (*itr == a.getTrueIdentity()) {
            superheroes.erase(itr);
            break;
        }
    }
}

Team operator+(const Team &a, const Team &b) {
    Team resultingTeam;
    resultingTeam.superheroes = a.superheroes;
    list<Superhero> bSuperheroes = b.superheroes;
    for (list<Superhero>::iterator itr = bSuperheroes.begin(); itr != bSuperheroes.end(); itr++) {
        resultingTeam.superheroes.push_back(*itr);
    }
    return resultingTeam;
}

Team operator+(const Team &a, const Superhero &b) {
    Team resultingTeam;
    resultingTeam.superheroes = a.superheroes;
    resultingTeam.superheroes.push_back(b);
    return resultingTeam;
}

Team operator+(const Superhero &a, const Superhero &b) {
    Team resultingTeam;
    resultingTeam += a;
    resultingTeam += b;
    return resultingTeam;
}

