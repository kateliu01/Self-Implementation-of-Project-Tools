#include <iostream>
#include <vector>
#include <mutex>
#include <cassert>

class MemoryPool {
public:
    MemoryPool(size_t block_size, size_t num_blocks)
        : block_size(block_size), capacity(num_blocks) {
        assert(block_size >= sizeof(void*));  // Ensure alignment
        pool.reserve(capacity);
        for (size_t i = 0; i < capacity; ++i) {
            void* block = ::operator new(block_size);
            pool.push_back(block);
            free_blocks.push_back(block);
        }
    }

    ~MemoryPool() {
        for (void* block : pool) {
            ::operator delete(block);
        }
    }

    void* allocate() {
        std::unique_lock<std::mutex> lock(mutex);
        if (free_blocks.empty()) {
            throw std::runtime_error("Memory pool is exhausted.");
        }
        void* block = free_blocks.back();
        free_blocks.pop_back();
        return block;
    }

    void deallocate(void* block) {
        std::unique_lock<std::mutex> lock(mutex);
        free_blocks.push_back(block);
    }

    // Additional features for handling fragmentation and performance
    // ...

private:
    size_t block_size;
    size_t capacity;
    std::vector<void*> pool;
    std::vector<void*> free_blocks;
    std::mutex mutex;
};

int main() {
    try {
        MemoryPool pool(sizeof(int), 10);

        int* ptr1 = static_cast<int*>(pool.allocate());
        *ptr1 = 42;
        std::cout << "Value: " << *ptr1 << std::endl;

        int* ptr2 = static_cast<int*>(pool.allocate());
        *ptr2 = 100;
        std::cout << "Value: " << *ptr2 << std::endl;

        pool.deallocate(ptr1);
        pool.deallocate(ptr2);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
