//
//  main.cpp
//  hw7
//
//  Created by Aditya Behal on 3/29/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include "costume.hpp"
#include "people.hpp"

using namespace std;

typedef map<Costume, pair<unsigned int, list<People>>> COSTUME_SHOP_TYPE;
typedef map<People, Costume> PEOPLE_TYPE;

typedef list<pair<Costume, pair<unsigned int, list<People>>>>
COSTUME_SHOP_TYPE_LIST;
typedef list<pair<People, Costume>> PEOPLE_TYPE_LIST;

// prototypes for the helper functions using maps
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(PEOPLE_TYPE& people);

// proptypes for the helper functions using only lists for the extra credit
void addCostumeList(COSTUME_SHOP_TYPE_LIST &costume_shop);
void rentCostumeList(COSTUME_SHOP_TYPE_LIST& costume_shop,
                     PEOPLE_TYPE_LIST& people);
void lookupList(COSTUME_SHOP_TYPE_LIST& costume_shop);
void printPeopleList(PEOPLE_TYPE_LIST& people);

int main(int argc, const char * argv[]) {
    // two data structures (maps) store all of the information for efficiency
    COSTUME_SHOP_TYPE costume_shop;
    PEOPLE_TYPE people;
    // two data structures (lists) store all of the information for extra credit
    COSTUME_SHOP_TYPE_LIST costume_shop_list;
    PEOPLE_TYPE_LIST people_list;
    char c;
    string extra_credit;
    if (argc == 2) {
        extra_credit = argv[1];
    }
    if (extra_credit != "" && extra_credit != string("extra_credit")) {
        cerr << "Invalid argument for extra credit option" << endl;
        return 1;
    }
    if (extra_credit == string("extra_credit")) {
        while (std::cin >> c) {
            if (c == 'a') {
                addCostumeList(costume_shop_list);
            } else if (c == 'r') {
                rentCostumeList(costume_shop_list,people_list);
            } else if (c == 'l') {
                lookupList(costume_shop_list);
            } else if (c == 'p') {
                printPeopleList(people_list);
            } else {
                std::cerr << "error unknown char " << c << std::endl;
                exit(0);
            }
        }
    } else {
        while (std::cin >> c) {
            if (c == 'a') {
                addCostume(costume_shop);
            } else if (c == 'r') {
                rentCostume(costume_shop,people);
            } else if (c == 'l') {
                lookup(costume_shop);
            } else if (c == 'p') {
                printPeople(people);
            } else {
                std::cerr << "error unknown char " << c << std::endl;
                exit(0);
            }
        }
    }
}

// add costumes to costume_shop and update frequency accordingly
void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    // O(1)
    Costume costume(costume_name);
    // O(log n)
    costume_shop[costume].first += num;
    if (num > 1) {
        cout << "Added " << num << " " << costume_name << " costumes." << endl;
    } else if (num == 1) {
        cout << "Added " << num << " " << costume_name << " costume." << endl;
    }
}

/* rent costumes by updating list<People> in costume_shop and people map
   accordingly */
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    // O(log n)
    // find the costume key in the costume shop mpa
    COSTUME_SHOP_TYPE::iterator costume_itr =
    costume_shop.find(Costume(costume_name));
    // O(log c)
    // find the people key in the people map
    PEOPLE_TYPE::iterator people_itr =
    people.find(People(first_name, last_name));
    if (costume_itr == costume_shop.end()) {
        cout << "The shop doesn't carry " << costume_name << " costumes." <<
        endl;
        if (people_itr == people.end()) {
            // O(log c)
            // if person doesn't exist, add the person to the people map
            people.insert(make_pair(People(first_name, last_name),
                                    Costume("NULL")));
        }
    } else if (costume_itr->second.first == 0) {
        cout << "No " << costume_name << " costumes available." << endl;
        if (people_itr == people.end()) {
            // O(log c)
            // if person doesn't exist, add the person to the people map
            people.insert(make_pair(People(first_name, last_name),
                                    Costume("NULL")));
        }
    } else if (people_itr != people.end() && people_itr->second.name() ==
               costume_name) {
        cout << first_name << " " << last_name << " already has a " <<
        costume_name << " costume." << endl;
    } else {
        if (people_itr == people.end()) {
            // O(log c)
            // if person doesn't exist, add the person to the people map
            people.insert(make_pair(People(first_name, last_name),
                                    Costume(costume_name)));
            costume_itr->second.first--;
            // O(1)
            // add this person to the people list
            costume_itr->second.second.push_back(People(first_name, last_name));
            cout << first_name << " " << last_name << " rents a " <<
            costume_name << " costume." << endl;
        } else {
            // O(log n)
            costume_shop[people_itr->second].first++;
            list<People>::iterator people_list_itr =
            costume_shop[people_itr->second].second.begin();
            // O(m)
            // remove the person from the people's list in customer_shop map
            for ( ; people_list_itr !=
                 costume_shop[people_itr->second].second.end();
                 people_list_itr++) {
                if (people_list_itr->first() == first_name &&
                    people_list_itr->last() == last_name) {
                    // O(1)
                    costume_shop[people_itr->second].second.
                    erase(people_list_itr);
                    break;
                }
            }
            costume_itr->second.first--;
            // O(1)
            // add this person to list<People>
            costume_itr->second.second.push_back(People(first_name, last_name));
            if (people_itr->second.name() == "NULL") {
                cout << first_name << " " << last_name << " rents a " <<
                costume_name << " costume." << endl;
            } else {
                cout << first_name << " " << last_name << " returns a " <<
                people_itr->second.name() << " costume before renting a " <<
                costume_name << " costume." << endl;e
            }
            people_itr->second = Costume(costume_name);
        }
    }
}

// lookup by costume
void lookup(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    std::cin >> costume_name;
    // O(log n)
    // find costume key in custome_shop
    COSTUME_SHOP_TYPE::iterator shop_itr =
    costume_shop.find(Costume(costume_name));
    if (shop_itr == costume_shop.end()) {
        cout << "The shop doesn't carry " << costume_name << " costumes." <<
        endl;
    } else {
        cout << "Shop info for " << costume_name << " costumes:" << endl;
        if (shop_itr->second.first > 1) {
            cout << "  " << shop_itr->second.first << " copies available" <<
            endl;
        } else if (shop_itr->second.first == 1) {
            cout << "  " << shop_itr->second.first << " copy available" << endl;
        }
        if (!shop_itr->second.second.empty()) {
            if (shop_itr->second.second.size() > 1) {
                cout << "  " << shop_itr->second.second.size() <<
                " copies rented by:" << endl;
            } else if (shop_itr->second.second.size() == 1) {
                cout << "  " << shop_itr->second.second.size() <<
                " copy rented by:" << endl;
            }
            // O(m)
            // remove person from list<People>
            for (list<People>::iterator people_itr =
                 shop_itr->second.second.begin();
                 people_itr != shop_itr->second.second.end(); people_itr++) {
                cout << "    " << people_itr->first() << " " <<
                people_itr->last() << endl;
            }
        }
    }
}

// print people in people map
void printPeople(PEOPLE_TYPE& people) {
    if (people.size() > 1) {
        cout << "Costume info for the " << people.size() << " party attendees:"
        << endl;
    } else if (people.size() == 1) {
        cout << "Costume info for the " << people.size() << " party attendee:"
        << endl;
    }
    // O(c)
    // iterate over people map and print out their corresponding costumes
    for (PEOPLE_TYPE::iterator people_itr = people.begin(); people_itr !=
         people.end(); people_itr++) {
        cout << "  ";
        if (people_itr->second.name() == "NULL") {
            cout << people_itr->first.first() << " " << people_itr->first.last()
            << " does not have a costume." << endl;
        } else {
            cout << people_itr->first.first() << " " << people_itr->first.last()
            << " is wearing a " << people_itr->second.name() << " costume." <<
            endl;
        }
    }
}

// typedef map<Costume, pair<unsigned int, list<People>>> COSTUME_SHOP_TYPE;
// typedef map<People, Costume> PEOPLE_TYPE;
void addCostumeList(COSTUME_SHOP_TYPE_LIST& costume_shop_list) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    Costume costume(costume_name);
    COSTUME_SHOP_TYPE_LIST::iterator shop_itr = costume_shop_list.begin();
    bool alreadyPresent = false;
    // O(n)
    for ( ; shop_itr != costume_shop_list.end(); shop_itr++) {
        if (shop_itr->first.name() == costume_name) {
            shop_itr->second.first += num;
            alreadyPresent = true;
            break;
        }
    }
    if (!alreadyPresent) {
        list<People> ppl;
        // O(1)
        costume_shop_list.push_back(make_pair(Costume(costume_name),
                                              make_pair(num, ppl)));
    }
    if (num > 1) {
        cout << "Added " << num << " " << costume_name << " costumes." << endl;
    } else if (num == 1) {
        cout << "Added " << num << " " << costume_name << " costume." << endl;
    }
}

void rentCostumeList(COSTUME_SHOP_TYPE_LIST& costume_shop_list,
                     PEOPLE_TYPE_LIST& people_list) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    // find the costume in the costume shop
    COSTUME_SHOP_TYPE_LIST::iterator costume_itr = costume_shop_list.begin();
    // O(n)
    for ( ; costume_itr != costume_shop_list.end(); costume_itr++) {
        if (costume_itr->first.name() == costume_name) {
            break;
        }
    }
    // find the correct person in people
    // O(c)
    PEOPLE_TYPE_LIST::iterator people_itr = people_list.begin();
    for ( ; people_itr != people_list.end(); people_itr++) {
        if (people_itr->first.first() == first_name && people_itr->first.last()
            == last_name) {
            break;
        }
    }
    if (costume_itr == costume_shop_list.end()) {
        cout << "The shop doesn't carry " << costume_name << " costumes." <<
        endl;
        if (people_itr == people_list.end()) {
            // if person doesn't exist, add the person to people
            // O(1)
            people_list.push_back(make_pair(People(first_name, last_name),
                                            Costume("NULL")));
        }
    } else if (costume_itr->second.first == 0) {
        cout << "No " << costume_name << " costumes available." << endl;
        if (people_itr == people_list.end()) {
            // if person doesn't exist, add the person to people
            // O(1)
            people_list.push_back(make_pair(People(first_name, last_name),
            Costume("NULL")));
        }
    } else if (people_itr != people_list.end() && people_itr->second.name() ==
               costume_name) {
        cout << first_name << " " << last_name << " already has a " <<
        costume_name << " costume." << endl;
    } else {
        if (people_itr == people_list.end()) {
            // if person doesn't exist, add the person to the people map
            // O(1)
            people_list.push_back(make_pair(People(first_name, last_name),
            Costume(costume_name)));
            costume_itr->second.first--;
            // add this person to the people list
            // O(1)
            costume_itr->second.second.push_back(People(first_name, last_name));
            cout << first_name << " " << last_name << " rents a " <<
            costume_name << " costume." << endl;
        } else {
            COSTUME_SHOP_TYPE_LIST::iterator costume_itr2 =
            costume_shop_list.begin();
            // O(n)
            for ( ; costume_itr2 != costume_shop_list.end(); costume_itr2++) {
                if (costume_itr2->first.name() == people_itr->second.name()) {
                    costume_itr2->second.first++;
                    break;
                }
            }
            
            list<People>::iterator people_list_itr =
            costume_itr->second.second.begin();
            // O(m)
            // remove the person from the people's list in customer_shop map
            for ( ; people_list_itr !=
                 costume_itr->second.second.end();
                 people_list_itr++) {
                if (people_list_itr->first() == first_name &&
                    people_list_itr->last() == last_name) {
                    // O(1)
                    costume_itr->second.second.erase(people_list_itr);
                    break;
                }
            }
            costume_itr->second.first--;
            // O(1)
            // add this person to list<People>
            costume_itr->second.second.push_back(People(first_name, last_name));
            if (people_itr->second.name() == "NULL") {
                cout << first_name << " " << last_name << " rents a " <<
                costume_name << " costume." << endl;
            } else {
                cout << first_name << " " << last_name << " returns a " <<
                people_itr->second.name() << " costume before renting a " <<
                costume_name << " costume." << endl;
            }
            people_itr->second = Costume(costume_name);
        }
    }
}

void lookupList(COSTUME_SHOP_TYPE_LIST& costume_shop_list) {
    std::string costume_name;
    std::cin >> costume_name;
    // find costume in custome_shop
    COSTUME_SHOP_TYPE_LIST::iterator shop_itr =
    costume_shop_list.begin();
    // O(c)
    for ( ; shop_itr != costume_shop_list.end(); shop_itr++) {
        if (shop_itr->first.name() == costume_name) {
            break;
        }
    }
    if (shop_itr == costume_shop_list.end()) {
        cout << "The shop doesn't carry " << costume_name << " costumes." <<
        endl;
    } else {
        cout << "Shop info for " << costume_name << " costumes:" << endl;
        if (shop_itr->second.first > 1) {
            cout << "  " << shop_itr->second.first << " copies available" <<
            endl;
        } else if (shop_itr->second.first == 1) {
            cout << "  " << shop_itr->second.first << " copy available" << endl;
        }
        if (!shop_itr->second.second.empty()) {
            if (shop_itr->second.second.size() > 1) {
                cout << "  " << shop_itr->second.second.size() <<
                " copies rented by:" << endl;
            } else if (shop_itr->second.second.size() == 1) {
                cout << "  " << shop_itr->second.second.size() <<
                " copy rented by:" << endl;
            }
            // remove person from list<People>
            // O(m)
            for (list<People>::iterator people_itr =
                 shop_itr->second.second.begin();
                 people_itr != shop_itr->second.second.end(); people_itr++) {
                cout << "    " << people_itr->first() << " " <<
                people_itr->last() << endl;
            }
        }
    }
}

// print people in people list
void printPeopleList(PEOPLE_TYPE_LIST& people_list) {
    if (people_list.size() > 1) {
        cout << "Costume info for the " << people_list.size() <<
        " party attendees:"
        << endl;
    } else if (people_list.size() == 1) {
        cout << "Costume info for the " << people_list.size() <<
        " party attendee:"
        << endl;
    }
    // iterate over people map and print out their corresponding costumes
    // O(c)
    for (PEOPLE_TYPE_LIST::iterator people_itr = people_list.begin();
         people_itr !=
         people_list.end(); people_itr++) {
        cout << "  ";
        if (people_itr->second.name() == "NULL") {
            cout << people_itr->first.first() << " " << people_itr->first.last()
            << " does not have a costume." << endl;
        } else {
            cout << people_itr->first.first() << " " << people_itr->first.last()
            << " is wearing a " << people_itr->second.name() << " costume." <<
            endl;
        }
    }
}
