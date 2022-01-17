#ifndef LFTUBRLA_GTTC_STRUCTSBUILDER_STRUCTSBUILDER_
#define LFTUBRLA_GTTC_STRUCTSBUILDER_STRUCTSBUILDER_

/*
*	Z.S. Create this file for GTTC. at November 28, 2021.
*	-----------------------------------------------------------------------------------------
*  	| ������ܹ��������κλ���������ɣ������κ��ֽڶ��뷽ʽ������ṹ�岢ʹ���ԡ�void*����ʽ���أ�			|
*	| �ˡ�void*��ָ���ܹ�ǿ��ת��Ϊָ����ʵ�ṹ���ָ�룬���ܶ�ȡ����ʵ���ݡ�							|
*   -----------------------------------------------------------------------------------------
*  	| ���಻�Ƕ��̰߳�ȫ�ģ�����ζ�������Ҫ�ڶ��̳߳�����ʹ�ã�����뱣֤���ȡ������ֲ���Ԥ֪�Ĵ���	 	|
*	| push_back/push_front/insert �����ṩ�����ڴ��ݽṹ���е���������� 							|
*	| operator<< �����޷������д����������ͣ������������ͻ������� 								|
*   | �����޷������ṹ���к�����Ҫ�����乹�캯������Ľṹ��  										|
*   -----------------------------------------------------------------------------------------
*/

#include <deque>
#include <memory>
#include <utility>

#ifndef _LFUBRLA_CHANGE_ARG_
	#define _LFUBRLA_CHANGE_ARG_	// �Դ˺����εĲ����ں������óɹ���������
#endif

class StructsBuilder{

public:
	StructsBuilder(){

	}
	~StructsBuilder()	{
		release_memory();
	}

public:
	/************************************
	* ����˵��:	��δ�����Ľṹ������һ����
	* 
	* ����:		const T & data_ Ҫ�����ֵ
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& push_back(const T& data_) {
		_data.push_back(std::pair<std::size_t, void*>(sizeof(T), new_data(data_)));
		return *this;
	}
	/************************************
	* ����˵��:	��δ�����Ľṹ������һ����(����֧�ֽṹ�����������͵�����)
	* 
	* ����:		const T * data_ Ҫ����������ָ��
	* ����:		std::size_t size_ Ҫ���������Ĵ�С
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& push_back(const T* data_, std::size_t size_) {
		for (std::size_t i = 0; i < size_; ++i) {
			push_back(data_[i]);
		}
		return *this;
	}
	/************************************
	* ����˵��:	��δ�����Ľṹ��ǰ����һ����
	*
	* ����:		const T & data_ Ҫ�����ֵ
	*
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& push_front(const T& data_) {
		_data.push_front(std::pair<std::size_t, void*>(sizeof(T), new_data(data_)));
		return *this;
	}
	/************************************
	* ����˵��:	��δ�����Ľṹ��ǰ����һ����(����֧�ֽṹ�����������͵�����)
	* 
	* ����:		const T * data_ Ҫ����������ָ��
	* ����:		std::size_t size_ Ҫ���������Ĵ�С
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& push_front(const T* data_, std::size_t size_) {
		for (std::size_t i = 0; i < size_; ++i) {
			push_front(data_[i]);
		}
		return *this;
	}
	/************************************
	* ����˵��:	��δ�����Ľṹ���в���һ����
	* 
	* ����:		std::size_t position_ Ҫ���뵽��λ��(�±�[��0Ϊ��һ��])
	* ����:		const T & data_ Ҫ�����ֵ
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& insert(std::size_t position_, const T& data_) {
		_data.insert(_data.begin() + position_, std::pair<std::size_t, void*>(sizeof(T), new_data(data_)));
		return *this;
	}
	/************************************
	* ����˵��:	��δ�����Ľṹ���в���һ����(����֧�ֽṹ�����������͵�����)
	* 
	* ����:		std::size_t position_ Ҫ���뵽��λ��(�±�[��0Ϊ��һ��])
	* ����:		const T * data_ Ҫ����������ָ��
	* ����:		std::size_t size_ Ҫ���������Ĵ�С
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& insert(std::size_t position_, const T* data_, std::size_t size_) {
		for (std::size_t i = 0; i < size_; ++i) {
			insert(position_ + i, data_[i]);
		}
		return *this;
	}
	/************************************
	* ����˵��:	ԴԴ���ϵ���δ�����Ľṹ��ĩβ������
	* 
	* ����:		const T & data_ Ҫ�����ֵ
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	template<typename T> StructsBuilder& operator<<(const T& data_) {
		return push_back(data_);
	}
	/************************************
	* ����˵��:	�ӵ�ǰ�����Ľṹ���ж�ȡ���ڴ�
	* 
	* ����:		_LF_CHANGE_ARG_ void * & data_ �ɹ���ȡ�󣬸ýṹ��Ļᱻ�����ָ��ָ��ĵ�ַ
	* ����:		std::size_t byte_alignment_ �ṹ���ֽڶ��뷽ʽ(0ΪϵͳĬ���ֽڶ��뷽ʽ)
	* 
	* ����ֵ:	std::size_t �ɹ���ȡ�����ڴ���ռ�ֽڴ�С
	*************************************/
	std::size_t read_data(_LFUBRLA_CHANGE_ARG_ void*& data_, std::size_t byte_alignment_ = 0) const {
		std::size_t over_size = 0;
		if (byte_alignment_ == 0) {
			over_size = default_memory_setting(data_);
		}
		else {
			over_size = memory_setting(data_, byte_alignment_);
		}
		return over_size;
	}
	/************************************
	* ����˵��:	�жϵ�ǰ�Ƿ���δ�����κνṹ��
	* 
	* ����:		void
	* 
	* ����ֵ:	bool true:��ǰ�ṹ���ǿյģ�false:��ǰ�ṹ�岻Ϊ��
	*************************************/
	bool empty(void) const {
		return _data.empty();
	}
	/************************************
	* ����˵��:	����������ڹ���������
	* 
	* ����:		void
	* 
	* ����ֵ:	StructsBuilder& ��ǰ���������
	*************************************/
	StructsBuilder& clear(void) {
		release_memory();
		_data.clear();
		return *this;
	}

private:
	// ����һ���µ��ڴ�
	template<typename T> void* new_data(const T& data_) {
		return new T(data_);
	}
	// Ĭ���ֽڶ����»�ȡ��ǰ�����Ľṹ���ڴ�
	std::size_t default_memory_setting(_LFUBRLA_CHANGE_ARG_ void*& data_) const {
		std::size_t all_size = 0;
		std::deque<std::pair<std::size_t, void*> >::const_iterator itr;
		std::size_t max_size = 0;
		for (itr = _data.cbegin(); itr != _data.cend(); ++itr) {
			if (itr->first > max_size) {
				max_size = itr->first;
			}
			// Ĭ���ֽڶ����£��ṹ���ڴ����ǳ�����һ���ݵ��ڴ汶��ƫ��
			if (all_size % itr->first != 0) {
				std::size_t next_size = round_up(itr->first, all_size);
				push_nullptr(data_, all_size, next_size - all_size);
				all_size = next_size;
			}
			memory_push(data_, all_size, itr->second, itr->first);
			all_size += itr->first;
		}
		// Ĭ���ֽڶ����£��ṹ�����ڴ�������ṹ�������Ԫ��ռ���ڴ�ı���ƫ��
		if (all_size % max_size != 0) {
			std::size_t next_size = round_up(max_size, all_size);
			push_nullptr(data_, all_size, next_size - all_size);
			all_size = next_size;
		}
		return all_size;
	}
	// ��Ĭ���ֽڶ����»�ȡ��ǰ�����Ľṹ���ڴ�
	std::size_t memory_setting(_LFUBRLA_CHANGE_ARG_ void*& data_, std::size_t byte_alignment_) const {
		std::size_t all_size = 0;
		std::deque<std::pair<std::size_t, void*> >::const_iterator itr;
		std::size_t max_size = 0;
		for (itr = _data.cbegin(); itr != _data.cend(); ++itr) {
			// ��Ĭ���ֽڶ����£���ǰԪ�ص��ڴ���䷽ʽȡ����Ԫ�صĶ��뷽ʽ��ָ�����䷽ʽ�н�С��һ��
			std::size_t now_byte_alignment = std::min(itr->first, byte_alignment_);
			if (now_byte_alignment > max_size) {
				max_size = now_byte_alignment;
			}
			if (all_size % now_byte_alignment != 0) {
				std::size_t next_size = round_up(now_byte_alignment, all_size);
				push_nullptr(data_, all_size, next_size - all_size);
				all_size = next_size;
			}
			memory_push(data_, all_size, itr->second, itr->first);
			all_size += itr->first;
		}
		// ��Ĭ���ֽڶ����£��ṹ�����ڴ�������ʹ�ù������ƫ�����ı���ƫ��
		if (all_size % max_size != 0) {
			std::size_t next_size = round_up(max_size, all_size);
			push_nullptr(data_, all_size, next_size - all_size);
			all_size = next_size;
		}
		return all_size;
	}
	// ��ĳ�ڴ������µ��ڴ�
	std::size_t memory_push(_LFUBRLA_CHANGE_ARG_ void*& src_ptr_, std::size_t src_size_, const void* new_ptr_, std::size_t new_size_) const {
		char* tmp_data = (char*)std::malloc(src_size_ + new_size_);
		if (tmp_data == nullptr) {
			return 0;
		}
		std::memcpy(tmp_data, src_ptr_, src_size_);
		std::memcpy(tmp_data + src_size_, new_ptr_, new_size_);
		free(src_ptr_);
		src_ptr_ = tmp_data;
		return src_size_ + new_size_;
	}
	// ��ĳ�ڴ�������ֽ�
	std::size_t push_nullptr(_LFUBRLA_CHANGE_ARG_ void*& src_ptr_, std::size_t src_size_, std::size_t nullptr_size_) const {
		if (nullptr_size_ == 0) {
			return src_size_;
		}
		void* tmp_ptr = malloc(src_size_ + nullptr_size_);
		if (tmp_ptr == 0) {
			return 0;
		}
		std::memset(tmp_ptr, 0, src_size_ + nullptr_size_);
		std::memcpy(tmp_ptr, src_ptr_, src_size_);
		free(src_ptr_);
		src_ptr_ = tmp_ptr;
		return src_size_ + nullptr_size_;
	}
	// ��ȡĳ����ӽ�ĳֵ�������ı���
	std::size_t round_up(std::size_t num_, std::size_t max_num_) const {
		if (num_ == 0) {
			return max_num_;
		}
		std::size_t remainder = max_num_ % num_;
		if (remainder == 0) {
			return max_num_;
		}
		return num_ + max_num_ - remainder;
	}
	// �ͷ����������ڴ�
	void release_memory(void) {
		std::deque<std::pair<std::size_t, void*> >::iterator itr;
		for (itr = _data.begin(); itr != _data.end(); ++itr) {
			delete itr->second;
		}
	}

private:
	std::deque<std::pair<std::size_t,void*> > _data;
};

#endif