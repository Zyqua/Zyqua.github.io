#include<string>
#include<algorithm>
#include<vector>
#include<io.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>

struct post {
	std::string fileName, title, date;
	int weight;
	inline bool operator < (const post &b) const { return weight < b.weight; }
};
std::vector<post> posts;
std::vector<std::string> postName;

std::string GbkToUtf8(const char *src_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}
std::string Utf8ToGbk(const char *src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}
inline void readDir(std::string path, std::vector<std::string> &fileName) {
	long hFile = 0;
	struct _finddata_t fileInfo;
	if ((hFile = _findfirst((path + "\\*.*").c_str(), &fileInfo)) == -1) return;
	do {
		std::string name(fileInfo.name);
		if (name != std::string(".") && name != std::string("..")) fileName.push_back(std::string(fileInfo.name));
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
}
inline void getPosts(std::vector<std::string> &postName, std::vector<post> &posts) {
	std::ifstream inFile;
	for (std::vector<std::string>::iterator i = postName.begin(); i != postName.end(); ++i) {
		inFile.open(std::string(".\\source\\posts\\") + *i);
		post p;
		inFile >> p.title >> p.date >> p.weight;
		p.fileName = GbkToUtf8((*i).c_str());
		posts.push_back(p);
		inFile.close();
	}
}
inline void print(std::vector<post> &posts) {
	std::ofstream outFile;
	outFile.open(".\\posts.html");
	outFile << "<!DOCTYPE html>\n<head>\n\t<meta chatset=\"utf-8\"/>\n\t<title>n-kw && n-c by others</title>\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"./styles.css\"/>\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"./markdownStyles.css\"/>\n</head>\n<body>\n<div class=\"body\">\n\t<p class=\"title\">striving & singing</p>\n\t<ul class=\"menu\">" << std::endl;
	for (std::vector<post>::iterator i = posts.begin(); i != posts.end(); ++i) {
		//<li><a target="_top" href="./posts/.html">title</a></li>
		outFile << "\t\t<li><a target=\"_top\" href=\"./posts/" << i->fileName << ".html\">"
				<< i->title << "</a></li>" << std::endl;
	}
	outFile << "\t</ul>\n\t<a href=\"index.html\" class=\"link\" style=\"display:block; text-align:center;\">return</a>\n</div>\n</body>";
	outFile.close();
}

int main() {
	system("chcp 65001");
	readDir(std::string(".\\source\\posts"), postName);
	//for (std::vector<std::string>::iterator i = postName.begin(); i != postName.end(); ++i) std::cout << *i << std::endl;
	getPosts(postName, posts);
	for (std::vector<post>::iterator i = posts.begin(); i != posts.end(); ++i)
		std::cout << i->fileName << std::endl << i->title << ' ' << i->date << ' ' << i->weight << std::endl;
	std::sort(posts.begin(), posts.end());
	print(posts);
	while (1);
	return 0;
}
