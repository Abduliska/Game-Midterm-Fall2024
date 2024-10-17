#include "FileController.h"

FileController::FileController()
{
	m_handle = nullptr;
	m_readSuccess = false;
	m_thread = {};
}

FileController::~FileController()
{
}

string FileController::GetCurDirectory()
{
	char buff[FILENAME_MAX];
	M_ASSERT(GetCurrentDir(buff, FILENAME_MAX) != nullptr, "Could not get current directory.");
	return string(buff);
}


int FileController::GetFileSize(string _filePath)
{
	m_handle = nullptr;
	if (fopen_s(&m_handle, _filePath.c_str(), "rb") != 0 || !m_handle)
	{
		std::cerr << "Error: Could not open file: " << _filePath << std::endl;
		return -1;
	}

	if (fseek(m_handle, 0, SEEK_END) != 0)
	{
		std::cerr << "Error: Could not seek to end of file: " << _filePath << std::endl;
		fclose(m_handle);
		return -1;
	}

	int fileSize = std::ftell(m_handle);
	if (fileSize == -1L)
	{
		std::cerr << "Error: Could not determine file size: " << _filePath << std::endl;
		fclose(m_handle);
		return -1;
	}

	fclose(m_handle);
	return fileSize;
}


bool FileController::ReadFile(string _filePath, unsigned char* _buffer, unsigned int _bufferSize)
{
	m_handle = nullptr;
	m_readSuccess = false;
	M_ASSERT(fopen_s(&m_handle, _filePath.c_str(), "rb") == 0, "Could not open file.");
	if (m_handle != nullptr)
	{
		M_ASSERT(fread(_buffer, 1, _bufferSize, m_handle) == _bufferSize, "All bytes not read from file.");
		M_ASSERT(ferror(m_handle) == 0, "Error reading from file.");
		M_ASSERT(fclose(m_handle) == 0, "Could not close file");
		m_readSuccess = true;
	}
	if (m_thread.joinable())
	{
		m_thread.detach();
	}
	return m_readSuccess;
}

void FileController::ReadFileAsync(string _filePath, unsigned char* _buffer, unsigned int _bufferSize)
{
	m_thread = std::thread(&FileController::ReadFile, this, _filePath, _buffer, _bufferSize);
}

