#include <iostream>
#include <cassert>

class Vector {
 private:
  struct SharedBuffer {
    double* data;
    size_t ref_count;
    size_t capacity;

    SharedBuffer(size_t n) : data(new double[n]), ref_count(1), capacity(n) {}
    
    ~SharedBuffer() {
      delete[] data;
    }
    
    void incr_ref() {
      ++ref_count;
    }
    
    void decr_ref() {
      --ref_count;
      if (ref_count == 0) {
        delete this;
      }
    }
    SharedBuffer* copy_part(size_t copy_size, size_t offset) {
      SharedBuffer* new_buffer = new SharedBuffer(copy_size);
      std::copy(data + offset, data + offset + copy_size, new_buffer->data);
      decr_ref();
      return new_buffer;
    }
  };

  SharedBuffer* buffer_;
  size_t offset_;
  size_t size_;
  
  mutable bool const_locked_;
  mutable bool write_locked_;

  void detach_if_needed() {
    if (buffer_->ref_count > 1) {
      buffer_ = buffer_->copy_part(size_, offset_);
      offset_ = 0;
    }
  }

 public:
  Vector(size_t size) 
      : buffer_(new SharedBuffer(size)),
        offset_(0),
        size_(size),
        const_locked_(false),
        write_locked_(false) {}

  Vector(const Vector& other)
      : buffer_(other.buffer_),
        offset_(other.offset_),
        size_(other.size_),
        const_locked_(false),
        write_locked_(false) {
    buffer_->incr_ref();
  }

  Vector(const Vector& other, size_t offset, size_t size)
      : buffer_(other.buffer_),
        offset_(other.offset_ + offset),
        size_(size),
        const_locked_(false),
        write_locked_(false) {
    assert(offset + size <= other.size_);
    assert(other.offset_ + offset + size <= other.buffer_->capacity);
    buffer_->incr_ref();
  }

  ~Vector() {
    buffer_->decr_ref();
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      buffer_->decr_ref();
      buffer_ = other.buffer_;
      buffer_->incr_ref();
      offset_ = other.offset_;
      size_ = other.size_;
      const_locked_ = false;
      write_locked_ = false;
    }
    return *this;
  }

  double& operator[](int index) {
    assert(index < size_ && index >= 0);
    assert(!const_locked_);
    detach_if_needed();
    return buffer_->data[offset_ + index];
  }

  const double& operator[](int index) const {
    assert(index < size_ && index >= 0);
    return buffer_->data[offset_ + index];
  }

  size_t size() const {
    return size_;
  }

  class Buffer {
   private:
    Vector* vector_;
    double* data_;

   public:
    Buffer(Vector* vec) : vector_(vec) {
      assert(!vector_->write_locked_);
      vector_->write_locked_ = true;
      vector_->detach_if_needed();
      data_ = vector_->buffer_->data + vector_->offset_;
    }
    
    ~Buffer() {
      vector_->write_locked_ = false; 
    }
    
    double* get() const { return data_; }
  };

  class ConstBuffer {
   private:
    const Vector* vector_;
    const double* data_;

   public:
    ConstBuffer(const Vector* vec) : vector_(vec) {
      assert(!vector_->write_locked_);
      vector_->const_locked_ = true;
      data_ = vector_->buffer_->data + vector_->offset_;
    }
    
    ~ConstBuffer() {
      vector_->const_locked_ = false;
    }
    
    const double* get() const { return data_; }
  };

  Buffer AquireBufferRAII() {
    return Buffer(this);
  }

  ConstBuffer AquireConstBufferRAII() const {
    return ConstBuffer(this);
  }

  double* AquireBuffer() {
    assert(!write_locked_);
    assert(!const_locked_);
    write_locked_ = true;
    detach_if_needed();
    return buffer_->data + offset_;
  }

  void ReleaseBuffer() {
    write_locked_ = false;
  }

  const double* AquireConstBuffer() const {
    assert(!write_locked_);
    const_locked_ = true;
    return buffer_->data + offset_;
  }

  void ReleaseConstBuffer() const {
    const_locked_ = false;
  }
};

int main() {
  return 0;
}
