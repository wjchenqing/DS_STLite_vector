#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <vector>

namespace sjtu {
template<typename T>
class vector {
public:
    class const_iterator;
    class iterator {
        friend class vector;
        friend class const_iterator;
    public:
         vector *point;
         size_t cur_pos;
    public:
        iterator(vector *obj, size_t cur) { point = obj; cur_pos = cur;}
        iterator(const iterator &other) { point = other.point; cur_pos = other.cur_pos;}
        iterator(const const_iterator &other) { point = other.point; cur_pos = other.cur_pos;}

        iterator operator+(const int &n) const {
            iterator tmp = *this;
            tmp.cur_pos += n;
            return tmp;
        }
        iterator operator-(const int &n) const {
            iterator tmp = *this;
            tmp.cur_pos -= n;
            return tmp;
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (point != rhs.point) throw invalid_iterator ();
            return cur_pos - rhs.cur_pos;
        }
        iterator& operator+=(const int &n) {
            cur_pos += n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            cur_pos -= n;
            return  *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++cur_pos;
            return tmp;
        }
        iterator& operator++() {
            ++cur_pos;
            return *this;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --cur_pos;
            return tmp;
        }
        iterator& operator--() {
            --cur_pos;
            return *this;
        }

        T& operator*() const{ return *(point->storage[cur_pos]);}		// *it
        bool operator==(const iterator &rhs) const { return (point == rhs.point) && (cur_pos == rhs.cur_pos);}
        bool operator==(const const_iterator &rhs) const { return (point == rhs.point) && (cur_pos == rhs.cur_pos);}
        bool operator!=(const iterator &rhs) const { return (point != rhs.point) || (cur_pos != rhs.cur_pos);}
        bool operator!=(const const_iterator &rhs) const { return (point != rhs.point) || (cur_pos != rhs.cur_pos);}
    };
    class const_iterator{
        friend class vector;
        friend class iterator;
    public:
        vector *point;
        size_t cur_pos;
    public:
        const_iterator(vector *obj, size_t cur) { point = obj; cur_pos = cur;}
        const_iterator(const iterator &other) { point = other.point; cur_pos = other.cur_pos;}
        const_iterator(const const_iterator &other) { point = other.point; cur_pos = other.cur_pos;}

        const_iterator operator+(const int &n) const {
            const_iterator tmp = *this;
            tmp.cur_pos += n;
            return tmp;
        }
        const_iterator operator-(const int &n) const {
            const_iterator tmp = *this;
            tmp.cur_pos -= n;
            return tmp;
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (point != rhs.point) throw invalid_iterator ();
            return cur_pos - rhs.cur_pos;
        }
        const_iterator& operator+=(const int &n) {
            cur_pos += n;
            return *this;
        }
        const_iterator& operator-=(const int &n) {
            cur_pos -= n;
            return  *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++cur_pos;
            return tmp;
        }
        const_iterator& operator++() {
            ++cur_pos;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --cur_pos;
            return tmp;
        }
        const_iterator& operator--() {
            --cur_pos;
            return *this;
        }

        const T& operator*() const{ return *(point->storage[cur_pos]);}		// *it
        bool operator==(const iterator &rhs) const { return (point == rhs.point) && (cur_pos == rhs.cur_pos);}
        bool operator==(const const_iterator &rhs) const { return (point == rhs.point) && (cur_pos == rhs.cur_pos);}
        bool operator!=(const iterator &rhs) const { return (point != rhs.point) || (cur_pos != rhs.cur_pos);}
        bool operator!=(const const_iterator &rhs) const { return (point != rhs.point) || (cur_pos != rhs.cur_pos);}
    };

private:
    T **storage = nullptr;
    size_t max_size;
    size_t cur_size;

    void double_size() {
        T **tmp = storage;
        storage = new T*[max_size * 2];
        for (size_t i = 0; i < cur_size; ++i) storage[i] = new T(*(tmp[i]));
        for (size_t i = 0; i < max_size; ++i) delete tmp[i];
        max_size *= 2;
        delete [] tmp;
    }

public:
    vector(size_t ini_size = 16) {
        max_size = ini_size;
        storage = new T*[ini_size];
        cur_size = 0;
    }
    vector(const vector &other) {
        max_size = other.max_size;
        cur_size = other.cur_size;
        storage = new T*[max_size];
        for (size_t i = 0; i < cur_size; ++i) storage[i] = new T(*(other.storage[i]));
    }
    vector(const std::vector<T> &other) {
        max_size = other.capacity();
        cur_size = other.size();
        storage = new T*[max_size];
        for (size_t i = 0; i < cur_size; ++i) storage[i] =new T(*(other[i]));
    }

    ~vector() {
        for (size_t i = 0; i < cur_size; ++i) delete storage[i];
        delete [] storage;
    }

    vector &operator=(const vector &other) {
        if (&other == this)
            return *this;
        for (size_t i = 0; i < cur_size; ++i) delete storage[i];
        delete [] storage;
        max_size = other.max_size;
        cur_size = other.cur_size;
        storage = new T*[max_size];
        for (size_t i = 0; i < cur_size; ++i) storage[i] = new T(*(other.storage[i]));
        return *this;
    }
    T & at(const size_t &pos) {
        if (pos < 0 || pos >= cur_size) throw index_out_of_bound();
        return *(storage[pos]);
    }
    const T & at(const size_t &pos) const {
        if (pos < 0 || pos >= cur_size) throw index_out_of_bound();
        return *(storage[pos]);
    }
    T & operator[](const size_t &pos) {
        if (pos < 0 || pos >= cur_size) throw index_out_of_bound();
        return *(storage[pos]);
    }
    const T & operator[](const size_t &pos) const {
        if (pos < 0 || pos >= cur_size) throw index_out_of_bound();
        return *(storage[pos]);
    }
    const T & front() const {
        if (cur_size == 0) throw container_is_empty();
        return *(storage[0]);
    }
    const T & back() const {
        if (cur_size == 0) throw container_is_empty();
        return *(storage[cur_size - 1]);
    }
    iterator begin() {
        return iterator(this,0);
    }
    const_iterator cbegin() const {
        return const_iterator(const_cast<vector*>(this),0);
    }
    iterator end() {
        return iterator(this, cur_size);
    }
    const_iterator cend() const {
        return const_iterator(const_cast<vector*>(this), cur_size);
    }
    bool empty() const {
        return cur_size == 0;
    }
    size_t size() const {
        return cur_size;
    }
    size_t capacity() const {
        return max_size;
    }
    void clear() {
        cur_size = 0;
    }
    iterator insert(iterator pos, const T &value) {
        if (cur_size >= max_size) double_size();
        if (pos.cur_pos == cur_size) storage[cur_size] = new T(value);
        else {
            for (size_t i = cur_size; i > pos.cur_pos; --i)
                storage[i] = storage[i - 1];
            storage[pos.cur_pos] = new T(value);
        }
        ++cur_size;
        return iterator(this, pos.cur_pos);
    }
    iterator insert(const size_t &ind, const T &value) {
        if (ind > cur_size) throw index_out_of_bound();
        if (cur_size >= max_size) double_size();
        if (ind == cur_size) storage[cur_size] = new T(value);
        else {
            for (size_t i = cur_size; i > ind; --i)
                storage[i] = storage[i - 1];
            storage[ind] = new T(value);
        }
        ++cur_size;
        return iterator(this, ind);
    }
    iterator erase(iterator pos) {
        T* tmp = storage[pos.cur_pos];
        for (size_t i = pos.cur_pos; i < cur_size - 1; ++i)
            storage[i] = storage[i + 1];
        --cur_size;
        delete tmp;
        return pos;
    }
    iterator erase(const size_t &ind) {
        if (ind >= cur_size) throw index_out_of_bound();
        T* tmp = storage[ind];
        for (size_t i = ind; i < cur_size - 1; ++i)
            storage[i] = storage[i + 1];
        --cur_size;
        delete tmp;
        return iterator(this, ind);
    }
    void push_back(const T &value) {
        if (max_size == cur_size) double_size();
        storage[cur_size++] = new T(value);
    }
    void pop_back() {
        if (cur_size == 0) throw container_is_empty();
        delete storage[--cur_size];
    }
};
}

#endif
