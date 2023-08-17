#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace generic {
template<typename T, std::size_t N>
  requires(N > 0)
class circular_buffer_iterator;

template<typename T, std::size_t N>
  requires(N > 0)
class circular_buffer
{
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using iterator = circular_buffer_iterator<T, N>;
  using const_iterator = circular_buffer_iterator<T const, N>;

  constexpr circular_buffer() = default;
  constexpr circular_buffer(value_type const (&values)[N])
    : size_(N)
    , tail_(N - 1)
  {
    std::copy(std::begin(values), std::end(values), data_.begin());
  }

  constexpr circular_buffer(const_reference v)
    : size_(N)
    , tail_(N - 1)
  {
    std::fill(data_.begin(), data_.end(), v);
  }

  constexpr size_type size() const noexcept { return size_; }
  constexpr size_type capacity() const noexcept { return N; }
  constexpr bool empty() const noexcept { return size_ == 0; }
  constexpr bool full() const noexcept { return size_ == N; }
  constexpr void clear() noexcept
  {
    size_ = 0;
    head_ = 0;
    tail_ = 0;
  }

  constexpr reference operator[](size_type const pos)
  {
    return data_[(head_ + pos) % N];
  }

  constexpr const_reference operator[](size_type const pos) const
  {
    return data_[(head_ + pos) % N];
  }

  constexpr reference at(size_type const pos)
  {
    if(pos < size_) {
      return data_[(head_ + pos) % N];
    }

    throw std::out_of_range("Index is out of range");
  }

  constexpr const_reference at(size_type const pos) const
  {
    if(pos < size_) {
      return data_[(head_ + pos) % N];
    }

    throw std::out_of_range("Index is out of range");
  }

  constexpr reference front()
  {
    if(size_ > 0) {
      return data_[head_];
    }

    throw std::logic_error("Buffer is empty");
  }

  constexpr const_reference front() const
  {
    if(size_ > 0) {
      return data_[head_];
    }

    throw std::logic_error("Buffer is empty");
  }

  constexpr reference back()
  {
    if(size_ > 0) {
      return data_[tail_];
    }

    throw std::logic_error("Buffer is empty");
  }

  constexpr const_reference back() const
  {
    if(size_ > 0) {
      return data_[tail_];
    }

    throw std::logic_error("Buffer is empty");
  }

  constexpr void push_back(T const& value)
  {
    if(empty()) {
      data_[tail_] = value;
      size_++;
    } else if(!full()) {
      data_[++tail_] = value;
      size_++;
    } else {
      head_ = (head_ + 1) % N;
      tail_ = (tail_ + 1) % N;
      data_[tail_] = value;
    }
  }

  constexpr void push_back(T&& value)
  {
    if(empty()) {
      data_[tail_] = value;
      size_++;
    } else if(!full()) {
      data_[++tail_] = std::move(value);
      size_++;
    } else {
      head_ = (head_ + 1) % N;
      tail_ = (tail_ + 1) % N;
      data_[tail_] = std::move(value);
    }
  }

  constexpr T pop_front()
  {
    if(empty()) {
      throw std::logic_error("Buffer is empty");
    }

    size_type index = head_;

    head_ = (head_ + 1) % N;
    size_--;

    return data_[index];
  }

  iterator begin() { return iterator(*this, 0); }

  iterator end() { return iterator(*this, size_); }

  const_iterator begin() const { return const_iterator(*this, 0); }

  const_iterator end() const { return const_iterator(*this, size_); }

private:
  std::array<value_type, N> data_;
  size_type head_ = 0;
  size_type tail_ = 0;
  size_type size_ = 0;

  friend circular_buffer_iterator<T, N>;
};

template<typename T, std::size_t N>
  requires(N > 0)
class circular_buffer_iterator
{
public:
  using self_type = circular_buffer_iterator<T, N>;
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  explicit circular_buffer_iterator(
    circular_buffer<T, N>& buffer,
    size_type const index
  )
    : buffer_(buffer)
    , index_(index)
  {
  }

  self_type& operator++()
  {
    if(index_ >= buffer_.get().size()) {
      throw std::out_of_range(
        "Iterator cannot be incremented past the end of the range"
      );
    }

    index_++;
    return *this;
  }

  self_type operator++(int)
  {
    self_type temp = *this;
    ++*this;

    return temp;
  }

  bool operator==(self_type const& other) const
  {
    return compatible(other) && index_ == other.index_;
  }

  bool operator!=(self_type const& other) const { return !(*this == other); }

  const_reference operator*() const
  {
    if(buffer_.get().empty() || !in_bounds()) {
      throw std::logic_error("Cannot dereferentiate the iterator");
    }

    return buffer_.get()
      .data_[(buffer_.get().head_ + index_) % buffer_.get().capacity()];
  }

  const_reference operator->() const
  {
    if(buffer_.get().empty() || !in_bounds()) {
      throw std::logic_error("Cannot dereferentiate the ierator");
    }

    return buffer_.get()
      .data_[(buffer_.get().head_ + index_) % buffer_.get().capacity()];
  }

  reference operator*()
  {
    if(buffer_.get().empty() || !in_bounds()) {
      throw std::logic_error("Cannot dereferentiate the iterator");
    }
    return buffer_.get()
      .data_[(buffer_.get().head_ + index_) % buffer_.get().capacity()];
  }

  reference operator->()
  {
    if(buffer_.get().empty() || !in_bounds()) {
      throw std::logic_error("Cannot dereferentiate the iterator");
    }
    return buffer_.get()
      .data_[(buffer_.get().head_ + index_) % buffer_.get().capacity()];
  }

  // forward iterator requirements

  // bidirectional iterator requirements
  self_type& operator--()
  {
    if(index_ <= 0) {
      throw std::out_of_range(
        "Iterator cannot be decremented before the beginning of the range"
      );
    }
    index_--;
    return *this;
  }

  self_type operator--(int)
  {
    self_type temp = *this;
    --*this;
    return temp;
  }

  // random access iterator requirements
  self_type operator+(difference_type offset) const
  {
    self_type temp = *this;
    return temp += offset;
  }

  self_type operator-(difference_type offset) const
  {
    self_type temp = *this;
    return temp -= offset;
  }

  difference_type operator-(self_type const& other) const
  {
    return index_ - other.index_;
  }

  self_type& operator+=(difference_type const offset)
  {
    difference_type next = (index_ + next) % buffer_.get().capacity();
    if(index_ >= buffer_.get().size()) {
      throw std::out_of_range(
        "Iterator cannot be incremented past the bounds of the range"
      );
    }

    index_ = next;
    return *this;
  }

  self_type& operator-=(difference_type const offset)
  {
    return *this += -offset;
  }

  value_type& operator[](difference_type const offset)
  {
    return *((*this + offset));
  }

  value_type const& operator[](difference_type const offset) const
  {
    return *((*this + offset));
  }

  bool operator<(self_type const& other) const { return index_ < other.index_; }

  bool operator>(self_type const& other) const { return other < *this; }

  bool operator<=(self_type const& other) const { return !(other < *this); }

  bool operator>=(self_type const& other) const { return !(*this < other); }

private:
  bool compatible(self_type const& other) const
  {
    return buffer_.get().data_.data() == other.buffer_.get().data_.data();
  }

  bool in_bounds() const
  {
    return !buffer_.get().empty() &&
           (buffer_.get().head_ + index_) % buffer_.get().capacity() <=
             buffer_.get().tail_;
  }
  std::reference_wrapper<circular_buffer<T, N>> buffer_;
  size_type index_ = 0;
};

static_assert(std::is_swappable_v<circular_buffer_iterator<int, 10>>);

template<typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt
flatzip(
  InputIt1 first1,
  InputIt1 last1,
  InputIt2 first2,
  InputIt2 last2,
  OutputIt dest
)
{
  auto it1 = first1;
  auto it2 = first2;

  while(it1 != last1 && it2 != last2) {
    *dest++ = *it1++;
    *dest++ = *it2++;
  }

  return dest;
}
}

int
main()
{
  generic::circular_buffer<int, 3> a({1, 2, 3});
  assert(a[0] == 1);
  assert(a[1] == 2);
  assert(a[2] == 3);
}