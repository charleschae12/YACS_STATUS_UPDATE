#ifndef SCRAPER_H
#define SCRAPER_H
#include <string.h>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <thread>

#include <curl/curl.h>
#include <libxml/HTMLparser.h>

class Scraper
{
public:
    Scraper(std::unordered_map<std::string, WebTitle> & umap);
    ~Scraper();

    void startScraping(void);
    std::string getHeadline(std::string &webSite);

private:
    std::unordered_map<std::string, WebTitle> webSites;
//    std::vector<std::thread> threadIds;
};
#endif // SCRAPER_H