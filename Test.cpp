#include "sources/MagicalContainer.hpp"
#include "doctest.h"
#include <iostream>


using namespace ariel;

MagicalContainer container;
TEST_CASE("1) Test Add function: "){
    CHECK_NOTHROW(container.addElement(1));
    CHECK_NOTHROW(container.addElement(14));
    CHECK_NOTHROW(container.addElement(35));
    CHECK_NOTHROW(container.addElement(16));
}

TEST_CASE("2) Test remove function: "){
    container.addElement(3);
    CHECK_NOTHROW(container.removeElement(3));  
     container.addElement(5);
    CHECK_NOTHROW(container.removeElement(6));
    container.addElement(33);
    CHECK_NOTHROW(container.removeElement(33));
    CHECK_THROWS(container.removeElement(9));
    CHECK_THROWS(container.removeElement(29));
    CHECK_THROWS(container.removeElement(19));
}

TEST_CASE("3) Test class ascIter operations: "){
    MagicalContainer c;
    container.addElement(11);
    container.addElement(12);
    container.addElement(13);
    CHECK_NOTHROW(MagicalContainer::AscendingIterator ascIter(container));    
    CHECK_NOTHROW(MagicalContainer::AscendingIterator ascIter(c));
}
TEST_CASE("4) Test class crossIter operations: "){
    MagicalContainer co;
    container.addElement(131);
    container.addElement(112);
    container.addElement(123);
    CHECK_NOTHROW(MagicalContainer::SideCrossIterator crossIter(co));
}
TEST_CASE("5) Test class primeIter operations: "){
    MagicalContainer con;
    container.addElement(111);
    container.addElement(122);
    container.addElement(133);
    CHECK_NOTHROW(MagicalContainer::PrimeIterator primeIter(con));
}
TEST_CASE("6) Test operator++ operation: "){
    ariel::MagicalContainer c1;
    c1.addElement(6);
    c1.addElement(7);
    c1.addElement(8);
    MagicalContainer::AscendingIterator ascIter(c1);
    auto it = ascIter.begin();
    CHECK (*it == 6);
    ++it;
    CHECK (*it == 7);
    ++it;
    CHECK (*it == 8);
}
TEST_CASE("7) Test iterating over the SideCross order") {
    ariel::MagicalContainer c2;
    c2.addElement(1);
    c2.addElement(29);
    c2.addElement(3);
    c2.addElement(7);
    c2.addElement(12);
    MagicalContainer::SideCrossIterator sideCrossIter(c2);
    std::vector<int> result;
    // Iterate over the elements using the SideCrossIterator
    for (auto it = sideCrossIter.begin(); it != sideCrossIter.end(); ++it) {
        result.push_back(*it);
    }
    // Check the result
    std::vector<int> expected = {1, 3, 12};
    REQUIRE(result == expected);
}
TEST_CASE("8) Test for iterating on prime numbers") {
    ariel::MagicalContainer c3;
    c3.addElement(1);
    c3.addElement(2);
    c3.addElement(3);
    c3.addElement(4);
    c3.addElement(5);
    MagicalContainer::PrimeIterator primeIter(c3);
    std::vector<int> result;
    // Iterate over the elements using the PrimeIterator
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        result.push_back(*it);
    }
    // Check the result
    std::vector<int> expected = {2, 3, 5};
    CHECK(result == expected);
}

TEST_CASE("9) Test SideCrossIterator begin: ") {
    ariel::MagicalContainer c4;
    c4.addElement(1);
    c4.addElement(2);
    c4.addElement(3);
    c4.addElement(4);
    c4.addElement(5);
    MagicalContainer::SideCrossIterator sideIter(c4);
    // Get the iterator returned by begin()
    auto beginIter = sideIter.begin();
    // Assert the first element
    REQUIRE(*beginIter == 1);
}
TEST_CASE("10) Test SideCrossIterator end: ") {
    ariel::MagicalContainer c5;
    c5.addElement(1);
    c5.addElement(2);
    c5.addElement(3);
    c5.addElement(4);
    c5.addElement(5);
    MagicalContainer::SideCrossIterator sideIter(c5);
    // Get the iterator returned by end()
    auto endIter = sideIter.end();
    // Assert that the iterator is pointing to the end of the container
    REQUIRE(endIter == c5.getElements().end());
}
TEST_CASE("11) Test PrimeIterator begin: ") {
    ariel::MagicalContainer c6;
    c6.addElement(1);
    c6.addElement(2);
    c6.addElement(3);
    c6.addElement(4);
    c6.addElement(5);
    MagicalContainer::PrimeIterator primeIter(c6);
    // Get the iterator returned by begin()
    auto beginIter = primeIter.begin();
    // Assert the first prime number
    CHECK(*beginIter == 2);
}
TEST_CASE("12) Test PrimeIterator end: ") {
    ariel::MagicalContainer c7;
    c7.addElement(1);
    c7.addElement(2);
    c7.addElement(3);
    c7.addElement(4);
    c7.addElement(5);
    MagicalContainer::PrimeIterator primeIter(c7);
    // Get the iterator returned by end()
    auto endIter = primeIter.end();
    // Assert that the iterator is pointing to the end of the container
    CHECK(endIter == c7.getElements().end());
}
TEST_CASE("13) Test AscendingIterator begin: ") {
    ariel::MagicalContainer c8;
    c8.addElement(1);
    c8.addElement(2);
    c8.addElement(3);
    c8.addElement(4);
    c8.addElement(5);
    MagicalContainer::AscendingIterator ascIter(c8);
    // Get the iterator returned by begin()
    auto beginIter = ascIter.begin();
    // Check the first element
    CHECK(*beginIter == 1);
}

TEST_CASE("14) Test AscendingIterator end: ") {
    ariel::MagicalContainer c9;
    c9.addElement(5);
    c9.addElement(3);
    c9.addElement(1);
    c9.addElement(4);
    c9.addElement(2);
    MagicalContainer::AscendingIterator ascIter(c9);
    // Get the iterator returned by end()
    auto endIter = ascIter.end();
    // Assert that the iterator is pointing to the end of the container
    CHECK(endIter == c9.getElements().end());
}
TEST_CASE("15) Test adding operations: "){
   ariel::MagicalContainer _c;
    _c.addElement(5);
    MagicalContainer::AscendingIterator ascIter(_c);
    auto beginIter_ = ascIter.begin();
    CHECK(*beginIter_ == 5);
}    
TEST_CASE("15) Test iterating over the MagicalContainer with duplicate elements using AscendingIterator: ") {
    ariel::MagicalContainer c_6;
    c_6.addElement(1);
    c_6.addElement(2);
    c_6.addElement(2);
    c_6.addElement(3);
    c_6.addElement(3);
    c_6.addElement(3);
    MagicalContainer::AscendingIterator ascIter(c_6);
    std::vector<int> result;
    // Iterate over the elements using the AscendingIterator
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        result.push_back(*it);
    }
    // Check the result
    std::vector<int> expected = {1, 2, 2, 3, 3, 3};
    CHECK(result == expected);
}
TEST_CASE("16) Test removing elements from MagicalContainer: ") {
    ariel::MagicalContainer c_1;
    c_1.addElement(1);
    c_1.addElement(2);
    c_1.addElement(3);
    c_1.addElement(4);
    c_1.addElement(5);
    c_1.removeElement(2);
    c_1.removeElement(4);
    // Check the size of the container
    CHECK(c_1.size() == 3);

    // Check the elements in the container
    std::vector<int> expected = {1, 3, 5};
    CHECK(c_1.getElements() == expected);
}

TEST_CASE("17) Test empty MagicalContainer: ") {
    ariel::MagicalContainer c_2;
    // Check the size of an empty container
    CHECK(c_2.size() == 0);
    // Check that the elements vector is empty
    CHECK(c_2.getElements().empty());
}

TEST_CASE("18) Test iterating over an empty container: ") {
    ariel::MagicalContainer c_3;
    MagicalContainer::AscendingIterator ascIter(c_3);
    // Check that begin() and end() are equal for an empty container
    CHECK(ascIter.begin() == ascIter.end());
}

TEST_CASE("19) Test iterating over a container with duplicate elements: ") {
    ariel::MagicalContainer c_4;
    c_4.addElement(1);
    c_4.addElement(2);
    c_4.addElement(2);
    c_4.addElement(3);
    c_4.addElement(3);
    c_4.addElement(3);
    MagicalContainer::AscendingIterator ascIter(c_4);
    std::vector<int> result;
    // Iterate over the elements using the AscendingIterator
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        result.push_back(*it);
    }
    // Check the result
    std::vector<int> expected = {1, 2, 2, 3, 3, 3};
    CHECK(result == expected);
}
TEST_CASE("20) Test iterating over an empty MagicalContainer with AscendingIterator: ") {
    ariel::MagicalContainer c;
    MagicalContainer::AscendingIterator ascIter(c);
    // Check that begin() and end() are equal for an empty container
    CHECK(ascIter.begin() == ascIter.end());
}
