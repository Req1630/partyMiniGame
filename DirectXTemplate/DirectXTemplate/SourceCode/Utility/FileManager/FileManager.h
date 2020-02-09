#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class CFileManager
{
public:
	CFileManager();
	~CFileManager();

	// バイナリデータでの書き込み.
	template<class outDATA>
	static void BinaryWriting( const std::string& fileName, const outDATA& outData )
	{
		std::fstream fout;
		fout.open( fileName, std::ios::out | std::ios::binary | std::ios::trunc );

		if( !fout ) return;

		fout.write( reinterpret_cast<const char*>(std::addressof(outData)), 
			sizeof(outDATA) );

		fout.close();  //ファイルを閉じる

		return;
	}
	// バイナリデータでの読み込み.
	template<class inDATA>
	static void BinaryReading( const std::string& fileName, inDATA& inData )
	{
		std::fstream fin;
		fin.open( fileName, std::ios::in | std::ios::binary );

		if( !fin ) return;

		fin.read( reinterpret_cast<char*>(std::addressof(inData)), 
			sizeof(inDATA) );

		fin.close();  //ファイルを閉じる

		return;
	}

	// ファイルの読み込み.
	static std::vector<std::string> TextLoading( const std::string& fileName, char delimiter = ',' );
};

#endif	// #ifndef FILE_MANAGER_H.