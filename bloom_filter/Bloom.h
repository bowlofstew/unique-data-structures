#ifndef __BLOOM_H__
#define __BLOOM_H__

/* Bloom Struct
 *
 * int* bloomFilter - Bit array for inserted elements
 * int numHashes - Number of hash functions desired
 * int size - Size of the bloomFilter
 * int numElementsToBeExpected - number of elements expected to be inserted
 * int count - number of elements inserted into bloom filter
 * int bits - number of number of elements expected to be inserted
 * int bytes - 
 *
 */

struct bloom;

typedef struct bloom {
    unsigned int* bloomFilter;
    int numHashes;
    int size;
} Bloom;


/* Init the bloom filter.
 *
 * @param bloom - This is the newly constructed bloom filter.
 * @param size - size of the bloom filter.
 * @param falsePositiveRate - false positive  rate.
 *
 * @return returnValue - False if falsePositiveRate, true otherwise.
 *
 * k = numberHashFunctions
 * m = bits in filter
 * n = elements that are expected to be inserted
 *
 * Since the false positive rate is (1-e^(k*n/m))^k, we can optimize the bloom filter by choosing a ballpark value for n, then m, then the optimal value for k. Lastly, we will calculate the falsePositiveRate rate for n, m, and k. If if is unacceptable, change m and recalculate; otherwise we're done
 *
 * Given m and n, the optimal value for k is (m/n)ln(2).
 * http://billmill.org/bloomfilter-tutorial 
 *
 */

int init(Bloom* bloom, int size, int numHashes);

/* Inserts a given element.
 * 
 * @param bloom - Bloom to insert key into
 * @param input - key to input
 *
 * @return int - False if not initialized or falsePositiveRate, true otherwise.
 *
 */
void put(Bloom *bloom, const char* input);

/* Returns if the string is either definitely not or it might be in the bloom filter.
 *
 * @param bloom - Bloom to get key from
 * @param input - key to search for
 *
 * @return value - 1 if 'might be' in bloom filter, 0 otherwise
 *
 */
int get(Bloom *bloom, const char* input);

/* Frees the memory
 *
 * @param bloom - bloom to free
 * 
 * @return value - error code (if any)
 *
 */

int destruct(Bloom *bloom);

void setBit(Bloom* bloom, int position);
int getBit(Bloom* bloom, int position);
#endif
