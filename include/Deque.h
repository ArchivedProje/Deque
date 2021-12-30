// Copyright byteihq 2021 <kotov038@gmail.com>

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <vector>
#include <array>

template<typename T>
class Deque {
private:
    static constexpr size_t fixed_size_ = 100u;
    std::vector<std::array<T, fixed_size_>> data_;
    std::pair<size_t, size_t> begin_;
    std::pair<size_t, size_t> end_;
public:
    Deque() : begin_(0, 0), end_(0, 0) {}

    explicit Deque(size_t count, const T &value = T()) {
        while (count > fixed_size_) {
            std::array<T, fixed_size_> arr;
            std::fill(arr.begin(), arr.begin() + fixed_size_, value);
            data_.push_back(std::move(arr));
            count -= fixed_size_;
        }
        std::array<T, fixed_size_> arr;
        std::fill(arr.begin(), arr.begin() + count, value);
        data_.push_back(std::move(arr));
        begin_ = {0, 0};
        end_ = {data_.size() - 1, count};
    }

    [[nodiscard]] size_t size() const {
        if (begin_.first == end_.first) {
            return end_.second - begin_.second;
        }
        return fixed_size_ - begin_.second + end_.second + (end_.first - begin_.first - 1) * fixed_size_;
    }

    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    const T &front() const {
        return data_[begin_.first][begin_.second];
    }

    T &front() {
        return data_[begin_.first][begin_.second];
    }

    const T &back() const {
        return data_[end_.first][end_.second - 1];
    }

    T &back() {
        return data_[end_.first][end_.second - 1];
    }

    const T &operator[](size_t index) const {
        auto step = index % fixed_size_;
        index /= fixed_size_;
        return data_[begin_.first + index][step];
    }

    T &operator[](size_t index) {
        auto step = index % fixed_size_;
        index /= fixed_size_;
        return data_[begin_.first + index][step];
    }

    const T &at(size_t index) const {
        if (index > size()) {
            throw std::out_of_range("Index out of range");
        }
        auto step = index % fixed_size_;
        index /= fixed_size_;
        return data_[begin_.first + index][step];
    }

    T &at(size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        auto step = index % fixed_size_;
        index /= fixed_size_;
        return data_[begin_.first + index][step];
    }

    void push_front(const T& value) {
        if (data_.empty()) {
            std::array<T, fixed_size_> arr;
            arr[fixed_size_ / 2] = value;
            data_.push_back(std::move(arr));
            begin_.second = fixed_size_ / 2;
            end_.second = begin_.second + 1;
            return;
        }
        if (empty()) {
            data_[begin_.first][begin_.second] = value;
            ++end_.second;
            if (end_.second == fixed_size_) {
                end_.second = 0;
                ++end_.first;
            }
            return;
        }
        if (begin_.first == 0 && begin_.second == 0) {
            std::vector<std::array<T, fixed_size_>> new_arr(data_.size() * 3);
            new_arr[data_.size() - 1][fixed_size_ - 1] = value;
            for (size_t i = 0; i < data_.size(); ++i) {
                new_arr[i + data_.size()] = std::move(data_[i]);
            }
            begin_.first = data_.size() - 1;
            begin_.second = 0;
            data_ = std::move(new_arr);
            return;
        }
        if (begin_.second == 0) {
            --begin_.first;
            begin_.second = fixed_size_ - 1;
            data_[begin_.first][begin_.second] = value;
            return;
        }
        --begin_.second;
        data_[begin_.first][begin_.second] = value;
    }

    void push_front(T&& value) {
        if (data_.empty()) {
            std::array<T, fixed_size_> arr;
            arr[fixed_size_ / 2] = std::move(value);
            data_.push_back(std::move(arr));
            begin_.second = fixed_size_ / 2;
            end_.second = begin_.second + 1;
            return;
        }
        if (empty()) {
            data_[begin_.first][begin_.second] = std::move(value);
            ++end_.second;
            if (end_.second == fixed_size_) {
                end_.second = 0;
                ++end_.first;
            }
            return;
        }
        if (begin_.first == 0 && begin_.second == 0) {
            std::vector<std::array<T, fixed_size_>> new_arr(data_.size() * 3);
            new_arr[data_.size() - 1][fixed_size_ - 1] = std::move(value);
            for (size_t i = 0; i < data_.size(); ++i) {
                new_arr[i + data_.size()] = std::move(data_[i]);
            }
            begin_.first = data_.size() - 1;
            begin_.second = 0;
            data_ = std::move(new_arr);
            return;
        }
        if (begin_.second == 0) {
            --begin_.first;
            begin_.second = fixed_size_ - 1;
            data_[begin_.first][begin_.second] = std::move(value);
            return;
        }
        --begin_.second;
        data_[begin_.first][begin_.second] = std::move(value);
    }

    void push_back(const T &value) {
        ++end_.second;
        if (end_.second == fixed_size_) {
            end_.second = 0;
            ++end_.first;
            std::array<T, fixed_size_> arr;
            arr[0] = value;
            data_.push_back(arr);
            return;
        }
        if (data_.empty()) {
            std::array<T, fixed_size_> arr;
            arr[0] = std::move(value);
            data_.push_back(std::move(arr));
            return;
        }
        data_[end_.first][end_.second - 1] = value;
    }

    void push_back(T &&value) {
        ++end_.second;
        if (end_.second == fixed_size_) {
            end_.second = 0;
            ++end_.first;
            std::array<T, fixed_size_> arr;
            arr[0] = std::move(value);
            data_.push_back(arr);
            return;
        }
        if (data_.empty()) {
            std::array<T, fixed_size_> arr;
            arr[0] = std::move(value);
            data_.push_back(std::move(arr));
            return;
        }
        data_[end_.first][end_.second - 1] = std::move(value);
    }

    void pop_back() {
        data_[end_.first][end_.second - 1].~T();
        if (end_.second == 0) {
            if (end_.first == 0) return;
            end_.second = fixed_size_ - 1;
            --end_.first;
        } else {
            --end_.second;
        }
    }

};

#endif //DEQUE_DEQUE_H
