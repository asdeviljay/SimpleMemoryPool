#pragma once
class MyMemoryPool
{
private:
	struct pHeader {
		unsigned char* m_pChunk;
		struct pHeader* m_pNext;
	};
	struct pHeader* m_pChunkHead = nullptr;
	unsigned int m_availableMemorySize;
	const unsigned int headerSize = sizeof(m_pChunkHead);

public:
	MyMemoryPool();
	~MyMemoryPool();

	void init(unsigned int block_size, unsigned int block_number);
	void* alloc(unsigned int t_size);
	void release(void* p, unsigned int t_size);
	void showAvailable() const;
};