#pragma once

#include <iostream>

using namespace std;

template<class T>
class DynamicArray {
public:
    class _iterator; // declare that this class exists in the future
    class _const_iterator; // declare that this class exists in the future
    class _reverse_iterator; // declare that this class exists in the future
    class _const_reverse_iterator; // declare that this class exists in the future
    // +Iterator+
    class _iterator {
    private:
        DynamicArray *_da;
        int _i;
    public:
        friend _const_iterator; // declare that this class exists in the future
        friend _reverse_iterator; // declare that this class exists in the future
        friend _const_reverse_iterator; // declare that this class exists in the future

        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        //constructors:
        _iterator(DynamicArray &arr, int i) : _da(&arr), _i(i) {}
        _iterator(const _const_iterator &other) : _da(const_cast<DynamicArray<value_type> *>(other._da)), _i(other._i) {}
        _iterator(const _iterator &other) : _da(other._da), _i(other._i) {}
        _iterator(const _reverse_iterator &other) : _da(other._da), _i(other._i) {}
        _iterator(const _const_reverse_iterator &other) : _da(const_cast<DynamicArray<value_type> *>(other._da)), _i(other._i) {}
        ~_iterator() = default;

        //operator=
        _iterator &operator=(const _iterator &other) {
            if (this != &other) {
                if (other._da == _da) {
                    _i = other._i;
                }
            }
            return *this;
        }
        _iterator &operator=(const _const_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _iterator &operator=(const _reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _iterator &operator=(const _const_reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }

        // comparison with another _iterator
        bool operator==(const _iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _const_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _reverse_iterator &other) const {
            return ((_da == other._da) && (_i == other._i));
        }
        bool operator==(const _const_reverse_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator!=(const _iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator<(const _iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator>(const _iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator<=(const _iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator>=(const _iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _reverse_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_reverse_iterator &other) const {
            return _i >= other._i;
        }

        // smart-pointer _iterator methods
        reference operator*() {
            return _da->_arr[_i];
        }
        pointer operator->() {
            return &_da->_arr[_i];
        }

        // increment-decrement _iterator methods
        _iterator operator+(int num) const {
            return _iterator(*_da, _i + num);
        }
        _iterator operator-(int num) const {
            return _iterator(*_da, _i - num);
        }
        _iterator &operator++() {
            ++_i;
            return *this;
        }
        _iterator operator++(int) {
            _iterator temp(*this);
            ++_i;
            return temp;
        }
        _iterator &operator--() {
            --_i;
            return *this;
        }
        _iterator operator--(int) {
            _iterator temp(*this);
            --_i;
            return temp;
        }
    };

    // +Const Iterator+
    class _const_iterator {
    private:
        const DynamicArray *_da;
        int _i;
    public:
        friend _iterator; // declare that this class exists in the future
        friend _reverse_iterator; // declare that this class exists in the future
        friend _const_reverse_iterator; // declare that this class exists in the future

        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        _const_iterator(DynamicArray &arr, int i) : _da(&arr), _i(i) {}
        _const_iterator(const _const_iterator &other) : _da(other._da), _i(other._i) {}
        _const_iterator(const _iterator &other) : _da(other._da), _i(other._i) {}
        _const_iterator(const _reverse_iterator &other) : _da(other._da), _i(other._i) {}
        _const_iterator(const _const_reverse_iterator &other) : _da(other._da), _i(other._i) {}
        ~_const_iterator() = default;

        //operator=
        _const_iterator &operator=(const _iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _const_iterator &operator=(const _const_iterator &other) {
            if (this != &other) {
                if (other._da == _da) {
                    _i = other._i;
                }
            }
            return *this;
        }
        _const_iterator &operator=(const _reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _const_iterator &operator=(const _const_reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }

        // comparison with another _iterator
        bool operator==(const _iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _const_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _reverse_iterator &other) const {
            return ((_da == other._da) && (_i == other._i));
        }
        bool operator==(const _const_reverse_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator!=(const _iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator<(const _iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator>(const _iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator<=(const _iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator>=(const _iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _reverse_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_reverse_iterator &other) const {
            return _i >= other._i;
        }

        // smart-pointer _iterator methods
        reference operator*() const {
            return _da->_arr[_i];
        }
        pointer operator->() const {
            return &_da->_arr[_i];
        }

        // increment-decrement _iterator methods
        _const_iterator operator+(int num) const {
            return _const_iterator(*_da, _i + num);
        }
        _const_iterator operator-(int num) const {
            return _const_iterator(*_da, _i - num);
        }
        _const_iterator &operator++() {
            ++_i;
            return *this;
        }
        _const_iterator operator++(int) {
            _const_iterator temp(*this);
            ++_i;
            return temp;
        }
        _const_iterator &operator--() {
            --_i;
            return *this;
        }
        _const_iterator operator--(int) {
            _const_iterator temp(*this);
            --_i;
            return temp;
        }
    };

    // +Reverse _iterator+
    class _reverse_iterator {
        DynamicArray *_da;
        int _i;
    public:
        friend _iterator; // declare that this class exists in the future
        friend _const_iterator; // declare that this class exists in the future
        friend _const_reverse_iterator; // declare that this class exists in the future

        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        //constructors:
        _reverse_iterator(DynamicArray &arr, int i) : _da(&arr), _i(i) {}
        _reverse_iterator(const _const_iterator &other) : _da(const_cast<DynamicArray<value_type> *>(other._da)), _i(other._i) {}
        _reverse_iterator(const _iterator &other) : _da(other._da), _i(other._i) {}
        _reverse_iterator(const _reverse_iterator &other) : _da(other._da), _i(other._i) {}
        _reverse_iterator(const _const_reverse_iterator &other) : _da(const_cast<DynamicArray<value_type> *>(other._da)), _i(other._i) {}
        ~_reverse_iterator() = default;

        //operator=
        _reverse_iterator &operator=(const _iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _reverse_iterator &operator=(const _const_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _reverse_iterator &operator=(const _reverse_iterator &other) {
            if (this != &other) {
                if (other._da == _da) {
                    _i = other._i;
                }
            }
            return *this;
        }
        _reverse_iterator &operator=(const _const_reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }

        // comparison with another _iterator
        bool operator==(const _iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _const_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _reverse_iterator &other) const {
            return ((_da == other._da) && (_i == other._i));
        }
        bool operator==(const _const_reverse_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator!=(const _iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator<(const _iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator>(const _iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator<=(const _iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator>=(const _iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _reverse_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_reverse_iterator &other) const {
            return _i >= other._i;
        }

        // smart-pointer _iterator methods
        reference operator*() {
            return _da->_arr[_i];
        }
        pointer operator->() {
            return &_da->_arr[_i];
        }

        // increment-decrement _iterator methods
        _reverse_iterator operator+(int num) const {
            return _reverse_iterator(*_da, _i - num);
        }
        _reverse_iterator operator-(int num) const {
            return _reverse_iterator(*_da, _i + num);
        }
        _reverse_iterator &operator++() {
            --_i;
            return *this;
        }
        _reverse_iterator operator++(int) {
            _reverse_iterator temp(*this);
            --_i;
            return temp;
        }
        _reverse_iterator &operator--() {
            ++_i;
            return *this;
        }
        _reverse_iterator operator--(int) {
            _reverse_iterator temp(*this);
            ++_i;
            return temp;
        }
    };

    // +Const Reverse _iterator+
    class _const_reverse_iterator {
        const DynamicArray *_da;
        int _i;
    public:
        friend _iterator; // declare that this class exists in the future
        friend _const_iterator; // declare that this class exists in the future
        friend _reverse_iterator; // declare that this class exists in the future

        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        //constructors:
        _const_reverse_iterator(DynamicArray &arr, int i) : _da(&arr), _i(i) {}
        _const_reverse_iterator(const _const_iterator &other) : _da(other._da), _i(other._i) {}
        _const_reverse_iterator(const _iterator &other) : _da(other._da), _i(other._i) {}
        _const_reverse_iterator(const _reverse_iterator &other) : _da(other._da), _i(other._i) {}
        _const_reverse_iterator(const _const_reverse_iterator &other) : _da(other._da), _i(other._i) {}
        ~_const_reverse_iterator() = default;

        //operator=
        _const_reverse_iterator &operator=(const _iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _const_reverse_iterator &operator=(const _const_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _const_reverse_iterator &operator=(const _reverse_iterator &other) {
            if (other._da == _da) {
                _i = other._i;
            }
            return *this;
        }
        _const_reverse_iterator &operator=(const _const_reverse_iterator &other) {
            if (this != &other) {
                if (other._da == _da) {
                    _i = other._i;
                }
            }
            return *this;
        }

        // comparison with another _iterator
        bool operator==(const _iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _const_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator==(const _reverse_iterator &other) const {
            return ((_da == other._da) && (_i == other._i));
        }
        bool operator==(const _const_reverse_iterator &other) const {
            return (_da == other._da) && (_i == other._i);
        }
        bool operator!=(const _iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator!=(const _const_reverse_iterator &other) const {
            return !(*this == other);
        }
        bool operator<(const _iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator<(const _const_reverse_iterator &other) const {
            return _i < other._i;
        }
        bool operator>(const _iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator>(const _const_reverse_iterator &other) const {
            return _i > other._i;
        }
        bool operator<=(const _iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator<=(const _const_reverse_iterator &other) const {
            return _i <= other._i;
        }
        bool operator>=(const _iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _reverse_iterator &other) const {
            return _i >= other._i;
        }
        bool operator>=(const _const_reverse_iterator &other) const {
            return _i >= other._i;
        }

        // smart-pointer _iterator methods
        reference operator*() {
            return _da->_arr[_i];
        }
        pointer operator->() {
            return &_da->_arr[_i];
        }

        // increment-decrement _iterator methods
        _const_reverse_iterator operator+(int num) {
            return _const_reverse_iterator(*_da, _i - num);
        }
        _const_reverse_iterator operator-(int num) {
            return _const_reverse_iterator(*_da, _i + num);
        }
        _const_reverse_iterator &operator++() {
            --_i;
            return *this;
        }
        _const_reverse_iterator operator++(int) {
            _const_reverse_iterator temp(*this);
            --_i;
            return temp;
        }
        _const_reverse_iterator &operator--() {
            ++_i;
            return *this;
        }
        _const_reverse_iterator operator--(int) {
            _const_reverse_iterator temp(*this);
            ++_i;
            return temp;
        }
    };

    //constructors:
    DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}
    DynamicArray(const DynamicArray &other) : _arr(nullptr) {
        *this = other;
    }
    ~DynamicArray() {
        delete[] _arr;
    }

    //operator=
    DynamicArray &operator=(const DynamicArray &other) {
        if (this != &other) {
            _logicalSize = other._logicalSize;
            _physicalSize = other._physicalSize;
            delete[] _arr;
            _arr = new T[_physicalSize];
            for (int i = 0; i < _logicalSize; i++)
                _arr[i] = other._arr[i];
        }
        return *this;
    }

    //operators:
    const T &operator[](int i) const { return _arr[i]; }
    T &operator[](int i) { return _arr[i]; }

    //methods:
    void push_back(const T &value) {
        if (_logicalSize == _physicalSize)
            resize();
        _arr[_logicalSize++] = value;
    }
    const T &front() const { return _arr[0]; }
    int size() const { return _logicalSize; }
    int capacity() const { return _physicalSize; }
    bool empty() const { return _logicalSize == 0; }
    void clear() { _logicalSize = 0; }
    void insert(const _iterator &pos, const T &val) {
        if (_logicalSize == _physicalSize)
            resize();

        _iterator itrEnd = end();
        _iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
        while (itrCurrent != pos) {
            *itrCurrent = *itrPrev;
            itrCurrent = itrPrev--;
        }

        _iterator p = pos;
        *p = val;
        ++_logicalSize;
    }
    _iterator erase(const _iterator &iter) {
        T *tmp = new T[_physicalSize];
        int p = 0;
        int tempsize = _logicalSize;
        _iterator itr = this->begin(); //'ret' is the last erased position.
        _iterator ret = this->begin();
        for (int i = 0; i < _logicalSize; i++, itr++) {
            if (itr != iter) {//write if didn't found
                tmp[p] = _arr[i];
                p++;
            }
            else {//skip
                tempsize--;
                ret = itr; //remember the last erased place;
            }
        }
        _logicalSize = tempsize;
        delete[]_arr;
        _arr = tmp;
        return ret; //returns the last _iterator place in the array ('end() - 1' is the maximum value possible, 'begin()' is the minimum value possible.)
    }
    _iterator erase(const _iterator &first, const _iterator &last) {
        /* this method erases the range between 'first' and 'last - 1', and returns 'last' in case of success.
        in case of failure, the function returns 'begin() - 1'. */
        T *tmp = new T[_physicalSize];
        int p = 0;
        _iterator bgn = this->begin();
        _iterator end = this->end();
        _iterator itr = bgn;
        _iterator ret = bgn - 1; //in a good situation, 'ret' should be eventually 'last'.

        _iterator _first = const_cast<_iterator &>(first);
        _iterator _last = const_cast<_iterator &>(last);
        int tempsize = _logicalSize;
        for (int i = 0; i < _logicalSize; i++, itr++) {
            if ((itr < _first) || (itr >= _last)) {//write // erases the range between 'first' and 'last - 1'
                tmp[p] = _arr[i];
                p++;
            }
            else {//skip
                tempsize--;
                ret = _iterator(*this, p); //remember the last erased place;
            }
        }
        _logicalSize = tempsize;
        delete[]_arr;
        _arr = tmp;
        return ret; //in a good situation, 'ret' should be eventually 'last'.
    }
    void print() const {
        for (int i = 0; i < _logicalSize; i++)
            cout << _arr[i] << " ";
        cout << endl;
    }

    //ALL begin / end:
    _iterator begin() {
        return _iterator(*this, 0);
    }
    _iterator end() {
        return _iterator(*this, _logicalSize);
    }
    _const_iterator begin() const {
        return _const_iterator(*this, 0);
    }
    _const_iterator end() const {
        return _const_iterator(*this, _logicalSize);
    }
    _const_iterator cbegin() {
        return _const_iterator(*this, 0);
    }
    _const_iterator cend() {
        return _const_iterator(*this, _logicalSize);
    }
    _reverse_iterator rbegin() {
        return _reverse_iterator(*this, _logicalSize - 1);
    }
    _reverse_iterator rend() {
        return _reverse_iterator(*this, -1);
    }
    _const_reverse_iterator crbegin() {
        return _const_reverse_iterator(*this, _logicalSize - 1);
    }
    _const_reverse_iterator crend() {
        return _const_reverse_iterator(*this, -1);
    }

    //typedefs:
    typedef _iterator iterator; //define
    typedef _const_iterator const_iterator; //define
    typedef _reverse_iterator reverse_iterator; //define
    typedef _const_reverse_iterator const_reverse_iterator; //define

private:
    void resize() {
        _physicalSize *= 2;
        T *temp = new T[_physicalSize];
        for (int i = 0; i < _logicalSize; i++)
            temp[i] = _arr[i];

        delete[] _arr;
        _arr = temp;
    }

    int _logicalSize;
    int _physicalSize;
    T *_arr;
};
