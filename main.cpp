#include <iostream>
#include <cxxopts.hpp>
#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

void curl_download(const std::string &url) {
    CURL *curl_handle;
    static const char *pagefilename = "dblp.xml.gz";
    FILE *pagefile;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    pagefile = fopen(pagefilename, "wb");
    if (pagefile) {
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
        curl_easy_perform(curl_handle);
        fclose(pagefile);
    }
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    cxxopts::Options options("DBLParse-core", "The core of DBLParse");
    options.allow_unrecognised_options();
    options.add_options()
        ("h,help", "Show help")
        ("d,download", "Download with url", cxxopts::value<std::string>())
        ;

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("download")) {
        const std::string url = result["download"].as<std::string>();
        curl_download(url);
        return 0;
    }

    std::cout << options.help() << std::endl;
    return 0;
}
