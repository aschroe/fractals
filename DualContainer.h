#pragma once


/** This class implements a dual container, which holds two seperate container instances
 *  inside, one of which is the default container and can be swapped at any time. That way the
 *  container can be iterated while getting modified without allocating/deallocating memory
 */
template<typename Container>
class DualContainer {
public:
  typedef typename Container::iterator iterator;

  DualContainer() : primary(&c1), secondary(&c2) {}
  DualContainer(size_t initialSize) : primary(&c1), secondary(&c2), c1(initialSize), c2(initialSize) {}

  template<typename T>
  void push_back(T&& elem) { primary->push_back(std::forward<T>(elem)); }

  /** Swaps primary and secondary container and clears the primary container
   */
  void clear() {
    std::swap(primary, secondary);
    primary->clear();
  }

  bool empty() const { return primary->empty(); }

  iterator begin() { return primary->begin(); }
  iterator end() { return primary->end(); }


  Container& getSecondary() { return *secondary; }
   
private:
  Container c1, c2;
  Container* primary;
  Container* secondary;
};
