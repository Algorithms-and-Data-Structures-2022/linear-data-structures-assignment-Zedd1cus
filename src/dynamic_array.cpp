#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {
    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity_]{};
    size_ = 0;
  }

  DynamicArray::~DynamicArray() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  }

  void DynamicArray::Add(int value) {
    int* array;
    if (size_ < capacity_) {
      data_[size_] = value;
    } else {
      array = new int[capacity_ + kCapacityGrowthCoefficient];
      for (int i; i < size_; i++) {
        array[i] = data_[i];
      }
      delete[] data_;
      data_ = array;
      data_[size_] = value;
      capacity_ += kCapacityGrowthCoefficient;
    }
    size_ += 1;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index > size_ or index < 0) {
      return false;
    }
    int new_capacity;
    if (size_ < capacity_) {
      new_capacity = capacity_;
    } else if (size_ == capacity_) {
      new_capacity = capacity_ + kCapacityGrowthCoefficient;
    }

    int* array = new int[new_capacity]{};
    bool flag = false;
    for (int i = 0; i < size_ + 1; i++) {
      if (i == index) {
        array[i] = value;
        flag = true;
      } else if (flag == true) {
        array[i] = data_[i - 1];
      } else if (flag == false) {
        array[i] = data_[i];
      }
    }
    delete[] data_;
    data_ = array;
    size_ += 1;
    capacity_ = new_capacity;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= size_ || index < 0) {
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index < size_ and index >= 0) {
      int flag = false;
      int val_of_deleted_index = data_[index];
      for (int i = 0; i < size_; i++) {
        if (flag == true) {
          if (i == size_ - 1) {
            data_[i] = {};
          } else {
            data_[i] = data_[i + 1];
          }
        } else if (i == index) {
          flag = true;
          data_[i] = data_[i + 1];
        }
      }
      size_ = size_ - 1;
      return val_of_deleted_index;
    }
  }

  void DynamicArray::Clear() {
    delete[] data_;
    data_ = new int[capacity_]{};
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index < size_ and index >= 0) {
      return data_[index];
    }

    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < capacity_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      return false;
    }
    int* array = new int[new_capacity];
    for (int i = 0; i < size_; i++) {
      array[i] = data_[i];
    }
    delete data_;
    data_ = array;
    capacity_ = new_capacity;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment