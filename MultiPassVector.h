#pragma once

/** This class implements a vector, which won't delete or deallocate it's elements upon calling clear().
 *  It will simply reset the write position and overwrite previous elements.
 */
template<typename T>
class MultiPassVector {
public:
  typedef typename std::vector<T>::iterator iterator;

  MultiPassVector() : elements(20) { 
    pos = elements.begin(); 
  }

  MultiPassVector(size_t initialSize) : elements(initialSize) {
    pos = elements.begin();
  }

  template<typename U>
  void push_back(U&& elem) {
    if (pos == elements.end()) {
      // vector capacity reached -> reallocation necessary
      size_t prevSize = elements.size();
      elements.resize(static_cast<size_t>(prevSize*1.5));
      pos = elements.begin() + prevSize;
    }

    *pos = std::forward<U>(elem);
    ++pos;
  }

  void clear() {
    pos = elements.begin();
  }

  bool empty() const {
    return pos == elements.begin();
  }

  // Iteration interface
  iterator begin() { return elements.begin();  }
  iterator end() { return pos; }

private:
  std::vector<T> elements;
  typename std::vector<T>::iterator pos;
};