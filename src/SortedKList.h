#ifndef METNUM_TP2_SORTEDLIST_H
#define METNUM_TP2_SORTEDLIST_H

#include <list>
#include "io/IO.h"

template < typename T, typename C = std::less<T> >
class SortedKList {
public:
    SortedKList(size_t k, C comp = C()) : max(k), comparator(comp) {}

    void insertIfNecessary(const T& val) {
        if(l.size() < max || comparator(val, l.front())) {
            typename std::list<T>::iterator it;
            for (it = begin(); it != end(); ++it) {
                if (!comparator(val, *it)) {
                    break;
                }
            }
            l.insert(it, val);
            while (l.size() > max) {
                l.pop_front();
            }
        }
        assert(l.size() <= max);
    }

    typename std::list<T>::iterator begin() {
        return l.begin();
    }

    typename std::list<T>::iterator end() {
        return l.end();
    }

private:
    std::list<T> l;
    size_t max;
    C comparator;
};


#endif //METNUM_TP2_SORTEDLIST_H
