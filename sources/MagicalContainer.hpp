#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <iterator>
#include <list>
#include <string>
#include <fstream>
#include <climits>
#include <algorithm>

#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;
        std::vector<int>::const_iterator current;

    public:
        MagicalContainer() = default;
        MagicalContainer(MagicalContainer &other) = default;
        ~MagicalContainer() = default;
        void sortElements()
        {
            std::sort(elements.begin(), elements.end());
        }
        void addElement(int elem);
        int size() const;
        int getSize() const;
        void removeElement(int elem);
        const std::vector<int> &getElements() const;

    public:
        class AscendingIterator
        {
        private:
            const std::vector<int> *elements;
            std::vector<int>::const_iterator current;

        public:
            AscendingIterator(const MagicalContainer &cont)
                : elements(&cont.getElements()), current(elements->begin()) {}
            AscendingIterator()
                : elements(nullptr), current(0) {}
            AscendingIterator(const AscendingIterator &other)
                : elements(other.elements), current(other.current) {}

            ~AscendingIterator() {}

            AscendingIterator &operator=(const AscendingIterator &other)
            {
                if (elements != other.elements)
                {
                    throw std::runtime_error("Iterators are pointing to different containers");
                }

                current = other.current;
                return *this;
            }

            std::vector<int>::const_iterator begin() const
            {
                return elements->cbegin();
            }

            std::vector<int>::const_iterator end() const
            {
                return elements->cend();
            }

            AscendingIterator &operator++()
            {
                if (current == elements->end())
                {
                    throw runtime_error("Exceeding the last element boundry");
                }
                ++current;
                return *this;
            }

            bool operator==(const AscendingIterator &other) const
            {
                return current == other.current;
            }
            bool operator==(const std::vector<int>::const_iterator &ot) const
            {
                return current == ot;
            }

            bool operator!=(const AscendingIterator &other) const
            {
                return !(*this == other);
            }
            bool operator<(const AscendingIterator &other) const
            {
                return current < other.current;
            }

            bool operator<=(const AscendingIterator &other) const
            {
                return current <= other.current;
            }

            bool operator>(const AscendingIterator &other) const
            {
                return current > other.current;
            }

            bool operator>=(const AscendingIterator &other) const
            {
                return current >= other.current;
            }
            int operator*() const
            {
                if (current == elements->end())
                {
                    throw std::out_of_range("1) Iterator is out of range");
                }
                return *current;
            }
        };

        class SideCrossIterator
        {
        private:
            std::vector<int> &elements;
            std::vector<int>::size_type size_of_c1;
            std::vector<int>::size_type i;
            bool cur_p;

        public:
            SideCrossIterator(MagicalContainer &container)
                : elements(container.elements), size_of_c1(static_cast<std::vector<int>::size_type>(container.getSize())), i(0), cur_p(true)
            {
                std::sort(elements.begin(), elements.end(), std::less<int>());
            }
            SideCrossIterator(const SideCrossIterator &other) noexcept
                : elements(other.elements), size_of_c1(other.size_of_c1), i(other.i), cur_p(other.cur_p)
            {
            }

            SideCrossIterator(const SideCrossIterator &other, std::vector<int>::size_type i, bool cur_p) noexcept
                : elements(other.elements), size_of_c1(other.size_of_c1), i(i), cur_p(cur_p)
            {
            }
            ~SideCrossIterator() {}
            std::vector<int>::reference operator*() const
            {
                return elements[i];
            }

            std::vector<int>::pointer operator->() const
            {
                return &elements[i];
            }

            SideCrossIterator begin()
            {
                return SideCrossIterator(*this, 0, true);
            }

            SideCrossIterator end()
            {
                if (size_of_c1 == 0)
                {
                    return SideCrossIterator(*this, 0, true);
                }
                return SideCrossIterator(*this, size_of_c1, true);
            }

            SideCrossIterator &operator++()
            {
                if (i == size_of_c1)
                {
                    throw std::runtime_error("1) Iterator Increment Beyond End");
                }

                if (i == size_of_c1 / 2)
                {
                    i = size_of_c1;
                    return *this;
                }

                if (cur_p)
                {
                    i = size_of_c1 - i - 1;
                    cur_p = false;
                }
                else
                {
                    i = size_of_c1 - i;
                    cur_p = true;
                }
                return *this;
            }
            SideCrossIterator operator++(int)
            {
                if (i == size_of_c1)
                {
                    throw std::runtime_error("Iterator Increment Beyond End");
                }
                SideCrossIterator curr = *this;
                ++(*this);
                return curr;
            }

            bool operator==(const SideCrossIterator &c) const
            {
                return i == c.i && elements == c.elements;
            }

            bool operator!=(const SideCrossIterator &c) const
            {
                return !(*this == c);
            }
            bool operator>(const SideCrossIterator &other) const
            {
                if (i == -1 || other.i == -1)
                {
                    throw std::runtime_error("Comparing with end iterator");
                }

                if (cur_p)
                {
                    if (other.cur_p)
                    {
                        return i > other.i;
                    }
                    std::vector<int>::size_type new_i = size_of_c1 - other.i;
                    return i > new_i;
                }

                if (!other.cur_p)
                {
                    return i < other.i;
                }

                int new_i = size_of_c1 - i;
                return new_i >= other.i;
            }

            bool operator<(const SideCrossIterator &other) const
            {
                return !(*this > other || *this == other);
            }

            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if (elements != other.elements || size_of_c1 != other.size_of_c1)
                {
                    throw std::runtime_error("Iterators are pointing to different containers");
                }
                if (this != &other)
                {
                    elements = other.elements;
                    size_of_c1 = other.size_of_c1;
                    i = other.i;
                    cur_p = other.cur_p;
                }
                return *this;
            }
        };

        class PrimeIterator
        {
        private:
            /*
             using a pointer for a reference of the elements member.
            */
            const std::vector<int> *elements;
            std::vector<int>::size_type j;

        public:
            PrimeIterator(const ariel::MagicalContainer &container)
                : elements(&container.getElements()), j(0)
            {
                 advanceToNextPrime();
            }
            PrimeIterator(const PrimeIterator &other) noexcept
                : elements(other.elements), j(other.j)
            {
            }

            ~PrimeIterator() {}

            const std::vector<int>::value_type &operator*() const
            {
                return (*elements)[j];
            }

            const std::vector<int>::value_type *operator->() const
            {
                return &((*elements)[j]);
            }

            PrimeIterator begin() const
            {
                return PrimeIterator(*elements, 0);
            }

            PrimeIterator end() const
            {
                return PrimeIterator(*elements, elements->size());
            }

            PrimeIterator &operator=(const PrimeIterator &other)
            {
                if (elements != other.elements)
                {
                    throw std::runtime_error("Iterators are pointing to different containers");
                }

                j = other.j;
                return *this;
            }

            PrimeIterator &operator++()
            {
                if (j >= elements->size())
                {
                    throw runtime_error("Exceeding the last element boundary");
                }

                ++j;
                advanceToNextPrime();

                if (j >= elements->size())
                {
                    // Reached the end of the container, no more prime numbers
                    j = elements->size(); // Set j to the end position
                }

                return *this;
            }

            // PrimeIterator operator++(int)
            // {
            //     if (j == elements->size())
            //     {
            //         throw runtime_error("2) Exceeding the last element boundry");
            //     }
            //     PrimeIterator curr = *this;
            //     ++(*this);
            //     return curr;
            // }

            bool operator==(const PrimeIterator &other) const
            {
                if (j == elements->size() && other.j == other.elements->size())
                {
                    // Both iterators are at the end, they are considered equal
                    return true;
                }
                else if (j == elements->size() || other.j == other.elements->size())
                {
                    // One iterator is at the end, they are considered not equal
                    return false;
                }

                return (*elements)[j] == (*other.elements)[other.j];
            }
            bool operator==(const std::vector<int>::const_iterator &ot) const
            {
                return j == std::distance(elements->begin(), ot);
            }

            bool operator!=(const PrimeIterator &other) const
            {
                return !(*this == other);
            }

            bool operator>(const PrimeIterator &other) const
            {
                return j > other.j;
            }

            bool operator<(const PrimeIterator &other) const
            {
                return j < other.j;
            }

            bool operator>=(const PrimeIterator &other) const
            {
                return j >= other.j;
            }

            bool operator<=(const PrimeIterator &other) const
            {
                return j <= other.j;
            }

        private:
            PrimeIterator(const std::vector<int> &elems, std::vector<int>::size_type j)
                : elements(&elems), j(j) {}

            void advanceToNextPrime()
            {
                
                while (j < elements->size() && !isPrime((*elements)[j]))
                {
                    ++j;
                }
            }

            bool isPrime(int num) const
            {
                if (num < 2)
                {
                    return false;
                }
                int s_Num = sqrt(num);
                for (int i = 2; i <= s_Num; ++i)
                {
                    if (num % i == 0)
                    {
                        return false;
                    }
                }
                return true;
            }
        };
    };
} // namespace ariel

#endif // MAGICALCONTAINER_HPP
