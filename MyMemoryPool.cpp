#include "pch.h"
#include "MyMemoryPool.hpp"

#include <stdlib.h>
#include <iostream>


MyMemoryPool::MyMemoryPool()
{

}


MyMemoryPool::~MyMemoryPool()
{
	while (m_pChunkHead > m_pChunkHead->m_pNext && m_pChunkHead->m_pNext != nullptr) {
		m_pChunkHead = m_pChunkHead->m_pNext;
	}
	free(m_pChunkHead);
	std::cout << "Pool has been destroyed" << std::endl;
}

void MyMemoryPool::init(unsigned int block_size, unsigned int block_number) {
	unsigned int realBlockSize = block_size + headerSize;
	m_availableMemorySize = realBlockSize * block_number;
	m_pChunkHead = reinterpret_cast<pHeader*>(malloc(m_availableMemorySize));

	if (m_pChunkHead != nullptr) {
		//Todo : Manage memory
		m_pChunkHead->m_pNext = nullptr;
		std::cout << "Start pointer ->" << m_pChunkHead;
		std::cout << " Has memory = " << m_availableMemorySize << std::endl;
	}
}

void* MyMemoryPool::alloc(unsigned int t_size) {
	pHeader* pHead;
	if (m_pChunkHead != nullptr) {
		pHead = m_pChunkHead;
		int checkEnoughMemory = static_cast<int>(m_availableMemorySize - t_size - headerSize);
		if (checkEnoughMemory >= 0) {
			if (m_pChunkHead->m_pNext == nullptr) {
				pHead->m_pNext = reinterpret_cast<pHeader*>(reinterpret_cast<unsigned char*>(pHead) + t_size + headerSize);
				
				pHead = pHead->m_pNext;
				pHead->m_pNext = nullptr;
			}
			m_availableMemorySize = checkEnoughMemory;
		}
		else {
			pHead->m_pNext = nullptr;
			return nullptr;
		}
	}

	pHead = m_pChunkHead;
	m_pChunkHead = m_pChunkHead->m_pNext;
	std::cout << "Allocate pointer -> " << pHead << std::endl;
	showAvailable();
	return reinterpret_cast<void*>(pHead);
}

void MyMemoryPool::release(void* p, unsigned int t_size) {
	std::cout << "Release pointer -> " << p << std::endl;
	reinterpret_cast<pHeader*>(p)->m_pNext = m_pChunkHead;
	m_pChunkHead = reinterpret_cast<pHeader*>(p);
	m_availableMemorySize = m_availableMemorySize + t_size + headerSize;
	showAvailable();
}

void MyMemoryPool::showAvailable() const {
	std::cout << "Remainding Available Memory = " << m_availableMemorySize << std::endl;
}