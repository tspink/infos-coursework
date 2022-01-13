/*
 * Buddy Page Allocation Algorithm
 * SKELETON IMPLEMENTATION -- TO BE FILLED IN FOR TASK (2)
 */

/*
 * STUDENT NUMBER: s
 */
#include <infos/mm/page-allocator.h>
#include <infos/mm/mm.h>
#include <infos/kernel/kernel.h>
#include <infos/kernel/log.h>
#include <infos/util/math.h>
#include <infos/util/printf.h>

using namespace infos::kernel;
using namespace infos::mm;
using namespace infos::util;

#define MAX_ORDER	18

/**
 * A buddy page allocation algorithm.
 */
class BuddyPageAllocator : public PageAllocatorAlgorithm
{
private:
	/** Given a page descriptor, and an order, returns the buddy PGD.  The buddy could either be
	 * to the left or the right of PGD, in the given order.
	 * @param pgd The page descriptor to find the buddy for.
	 * @param order The order in which the page descriptor lives.
	 * @return Returns the buddy of the given page descriptor, in the given order.
	 */
	PageDescriptor *buddy_of(PageDescriptor *pgd, int order)
	{
        not_implemented();
	}

	/**
	 * Given a pointer to a block of free memory in the order "source_order", this function will
	 * split the block in half, and insert it into the order below.
	 * @param block_pointer A pointer to a pointer containing the beginning of a block of free memory.
	 * @param source_order The order in which the block of free memory exists.  Naturally,
	 * the split will insert the two new blocks into the order below.
	 * @return Returns the left-hand-side of the new block.
	 */
	PageDescriptor *split_block(PageDescriptor **block_pointer, int source_order)
	{
        not_implemented();
	}

	/**
	 * Takes a block in the given source order, and merges it (and it's buddy) into the next order.
	 * This function assumes both the source block and the buddy block are in the free list for the
	 * source order.  If they aren't this function will panic the system.
	 * @param block_pointer A pointer to a pointer containing a block in the pair to merge.
	 * @param source_order The order in which the pair of blocks live.
	 * @return Returns the new slot that points to the merged block.
	 */
	PageDescriptor **merge_block(PageDescriptor **block_pointer, int source_order)
	{
        not_implemented();
	}

public:
	/**
	 * Constructs a new instance of the Buddy Page Allocator.
	 */
	BuddyPageAllocator() {
		// Iterate over each free area, and clear it.
		for (unsigned int i = 0; i < ARRAY_SIZE(_free_areas); i++) {
			_free_areas[i] = NULL;
		}
	}

	/**
	 * Allocates 2^order number of contiguous pages
	 * @param order The power of two, of the number of contiguous pages to allocate.
	 * @return Returns a pointer to the first page descriptor for the newly allocated page range, or NULL if
	 * allocation failed.
	 */
	PageDescriptor *allocate_pages(int order) override
	{
		not_implemented();
	}

    /**
     * Marks a range of pages as available for allocation.
     * @param start A pointer to the first page descriptors to be made available.
     * @param count The number of page descriptors to make available.
     */
    void insert_page_range(PageDescriptor *start, uint64_t count) {
        not_implemented();
    }

    /**
     * Marks a range of pages as unavailable for allocation.
     * @param start A pointer to the first page descriptors to be made unavailable.
     * @param count The number of page descriptors to make unavailable.
     */
    void void remove_page_range(PageDescriptor *start, uint64_t count) {
        not_implemented();
    }

	/**
	 * Initialises the allocation algorithm.
	 * @return Returns TRUE if the algorithm was successfully initialised, FALSE otherwise.
	 */
	bool init(PageDescriptor *page_descriptors, uint64_t nr_page_descriptors) override
	{
		not_implemented();
	}

	/**
	 * Returns the friendly name of the allocation algorithm, for debugging and selection purposes.
	 */
	const char* name() const override { return "buddy"; }

	/**
	 * Dumps out the current state of the buddy system
	 */
	void dump_state() const override
	{
		// Print out a header, so we can find the output in the logs.
		mm_log.messagef(LogLevel::DEBUG, "BUDDY STATE:");

		// Iterate over each free area.
		for (unsigned int i = 0; i < ARRAY_SIZE(_free_areas); i++) {
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "[%d] ", i);

			// Iterate over each block in the free area.
			PageDescriptor *pg = _free_areas[i];
			while (pg) {
				// Append the PFN of the free block to the output buffer.
				snprintf(buffer, sizeof(buffer), "%s%lx ", buffer, sys.mm().pgalloc().pgd_to_pfn(pg));
				pg = pg->next_free;
			}

			mm_log.messagef(LogLevel::DEBUG, "%s", buffer);
		}
	}


private:
	PageDescriptor *_free_areas[MAX_ORDER+1];
};

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

/*
 * Allocation algorithm registration framework
 */
RegisterPageAllocator(BuddyPageAllocator);
