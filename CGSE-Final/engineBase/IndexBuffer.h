#pragma once

class IndexBuffer {
private: 
	unsigned int m_RendererID;
	unsigned int m_Count;
	const unsigned int* m_Data;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();


	void Bind() const;
	void UnBind() const;
	void AddCount(unsigned int count);
	void ReloadBufferDynamic();

	inline unsigned int GetCount() const { return m_Count; }
	inline void ClearCount(unsigned int baseCount = 0) { m_Count = baseCount; }
};