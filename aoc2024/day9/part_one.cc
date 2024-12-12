module;
#include <cstdint>
#include <iostream>
#include <regex>
#include <set>
#include <string_view>
#include <sys/types.h>

export module part_one;

export namespace part_one {

struct blockType {
  uint64_t id;
  uint64_t pos;
  uint64_t len;
};

struct emptyType {
  uint64_t pos;
  uint64_t len;
};

uint64_t result(const std::string_view input) {
  std::vector<blockType> blocks;
  std::vector<emptyType> empties;
  std::stringstream ss((std::string(input)));

  std::vector<char> diskspaces(input.begin(), input.end());
  uint32_t pos = 0;
  uint64_t id = 0;
  uint64_t iSpace = 0;
  for (auto spaceChar : diskspaces) {
    std::string space;
    space += spaceChar;
    uint64_t len = std::stoi(space);
    if (iSpace % 2 == 0) {
      if (len != 0) {
        blocks.push_back(blockType{id, pos, len});
        pos += len;
      }
      id++;
    } else {
      if (len != 0) {
        empties.push_back(emptyType{pos, len});
        pos += len;
      }
    }
    iSpace++;
  }
  std::vector<blockType> compactedBlocks;
  bool blocksCompacted = false;
  while (!blocksCompacted) {
    blockType block = blocks.back();
    bool blockCompacted = false;
    while (!blockCompacted) {
      emptyType empty = empties.front();
      if (empty.pos > block.pos) {
        blockCompacted = true;
        blocksCompacted = true;
      } else if (empty.len > block.len) {
        block.pos = empty.pos;
        compactedBlocks.push_back(block);
        empty.len = empty.len - block.len;
        empty.pos += block.len;
        empties.front() = empty;
        blockCompacted = true;
        blocks.pop_back();
      } else if (empty.len == block.len) {
        block.pos = empty.pos;
        compactedBlocks.push_back(block);
        empties.erase(empties.begin());
        blockCompacted = true;
        blocks.pop_back();
      } else { // empty.len < block.len
        block.len = block.len - empty.len;
        blocks.back() = block;
        compactedBlocks.push_back(blockType{block.id, empty.pos, empty.len});
        empties.erase(empties.begin());
      }
      if (empties.empty()) {
        blockCompacted = true;
        blocksCompacted = true;
      }
    }
  }

  uint64_t checksum = 0;
  for (auto &block : blocks) {
    checksum +=
        block.id * (block.pos * block.len + block.len * (block.len - 1) / 2);
  }
  for (auto &block : compactedBlocks) {
    checksum +=
        block.id * (block.pos * block.len + block.len * (block.len - 1) / 2);
  }

  /* while (!blocks.empty() || !compactedBlocks.empty()) {
    if (!blocks.empty() && !compactedBlocks.empty()) {
      if (blocks.front().pos < compactedBlocks.front().pos) {
        blockType block = blocks.front();
        for (int i = 0; i < block.len; i++) {
          std::cout << block.id << std::endl;
        }
        blocks.erase(blocks.begin());
      } else {
        {
          blockType block = compactedBlocks.front();
          for (int i = 0; i < block.len; i++) {
            std::cout << block.id << std::endl;
          }
          compactedBlocks.erase(compactedBlocks.begin());
        }
      }
    } else if (blocks.empty()) {
      blockType block = compactedBlocks.front();
      for (int i = 0; i < block.len; i++) {
        std::cout << block.id << std::endl;
      }
      compactedBlocks.erase(compactedBlocks.begin());
    } else {
      blockType block = blocks.front();
      for (int i = 0; i < block.len; i++) {
        std::cout << block.id << std::endl;
      }
      blocks.erase(blocks.begin());
    }
  } */
  return checksum;
}

} // namespace part_one