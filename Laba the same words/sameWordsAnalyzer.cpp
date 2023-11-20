#include <string>
#include "sameWordsAnalyzer.h"

sameWordsAnalyzer::sameWordsAnalyzer(logger log) : log(log) {}

sameWordsAnalyzer::~sameWordsAnalyzer()
{
    if (ofs.is_open()) {
        ofs.close();
    }
    if (ifs.is_open()) {
        ifs.close();
    }
}

void sameWordsAnalyzer::createListFromFile(const std::string path, char separator)
{
    log.log("������ ������ ���������� ");

    try
    {
        ifs.open(path);
        if (!ifs)
            throw std::runtime_error("������ ��� �������� ����� " + path);

        std::string word;
        while (getline(ifs, word, separator))
            mylist.pushBack(word);
        mylist.sort();

        ifs.close();
        log.log("��������� ���� ������� ������� ");
    }
    catch (const std::exception& e)
    {
        log.log("�������� ������: " + std::string(e.what()));
    }
}

void sameWordsAnalyzer::createReportFile(const std::string path)
{
    list::Node* current;
    if ((current = mylist.getHead()) == nullptr)
    {
        log.log("������� ������� ����� �� ������ ������ ");
        return;
    }

    try
    {
        ofs.open(path);
        if (!ofs)
            throw std::runtime_error("������ ��� �������� ����� " + path);

        while (current != nullptr)
        {
            std::string validstr = current->count > 1 && current->count < 5 ? " ����." : " ���.";

            ofs << "����� " << current->value << " ����������� " << current->count << validstr << std::endl;
            current = current->next;
        }

        ofs.close();
        log.log("��������� ������� ����������, ��� ������ ���� " + path);
    }
    catch (const std::exception& e)
    {
        log.log("�������� ������: " + std::string(e.what()));
    }
}
