#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "StandardIncludes.h"

class FileController : public Singleton<FileController>
{
public:
	FileController();
	virtual ~FileController();

	bool GetFileReadDone() { return !m_thread.joinable(); }
	bool GetFileReadSuccess() { return m_readSuccess; }


	string GetCurDirectory();
	int GetFileSize(string _filePath);
	bool ReadFile(string _filepath, unsigned char* _buffer, unsigned int _buffeSize);
	void ReadFileAsync(string _filePath, unsigned char* _buffer, unsigned int _bufferSize);

private:
	FILE* m_handle;
	thread m_thread;
	bool m_readSuccess;

};

#endif //FILE_CONTROLLER_H
