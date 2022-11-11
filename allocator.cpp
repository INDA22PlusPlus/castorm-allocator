#include <iostream>
#include <cstdint>
#include <unistd.h>

/**
 * Machine word size. Depending on the architecture,
 * can be 4 or 8 bytes.
 */
using word_t = intptr_t;
 
/**
 * Allocated block of memory. Contains the object header structure,
 * and the actual payload pointer.
 */
struct Block {
 
  // -------------------------------------
  // 1. Object header
 
  /**
   * Block size.
   */
  size_t size;
 
  /**
   * Whether this block is currently used.
   */
  bool used;
 
  /**
   * Next block in the list.
   */
  Block *next;
 
  // -------------------------------------
  // 2. User data
 
  /**
   * Payload pointer.
   */
  word_t data[1];
 
};

/**
 * Heap start. Initialized on first allocation.
 */
static Block *heapStart = nullptr;
 
/**
 * Current top. Updated on each allocation.
 */
static auto top = heapStart;

/**
 * Allocates a block of memory of (at least) `size` bytes.
 * word_t *alloc(size_t size) {
  ...
}
 */


/**
 * Aligns the size by the machine word.
 */
inline size_t align(size_t n) {
  return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

/**
 * Returns total allocation size, reserving in addition the space for
 * the Block structure (object header + first data word).
 *
 * Since the `word_t data[1]` already allocates one word inside the Block
 * structure, we decrease it from the size request: if a user allocates
 * only one word, it's fully in the Block struct.
 */
inline size_t allocSize(size_t size) {
  return size + sizeof(Block) - sizeof(std::declval<Block>().data);
}
 
/**
 * Requests (maps) memory from OS.
 */
Block *requestFromOS(size_t size) {
  // Current heap break.
  // WINDOWS !????!?!?!?!??!?!?
  auto block = (Block *)sbrk(0);                // (1)

  // OOM.
  if (sbrk(allocSize(size)) == (void *)-1) {    // (2)
    return nullptr;
  }

  return block;
}


int main() 
{
  
  return 0;
}

