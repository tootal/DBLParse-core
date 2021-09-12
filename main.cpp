#include <iostream>
#include <cxxopts.hpp>
// #include <curl/curl.h>
// #include <zlib.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

void dblp_download(const std::string &url) {
    /*
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
    */
}

int dblp_inflate(const std::string &fileName) {
    /*
    int ret;
    unsigned have;
    unsigned chunk_index = 0;
    z_stream strm;
    static constexpr int CHUNK = 16384;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) {
        return ret;
    }

    FILE *source;
    FILE *dest;

    source = fopen(fileName.c_str(), "rb");
    dest = fopen("dblp.xml", "wb");

    if (!source || !dest) {
        return -1;
    }

    // decompress until deflate stream ends or end of file
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0) {
            break;
        }
        strm.next_in = in;

        // run inflate on input until output buffer not full
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
            std::cout << "DBLP Inflate Chunk Index: " << (++chunk_index) << std::endl;
        } while (strm.avail_out == 0);
    } while (strm.avail_out == 0);

    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
    */
   return 0;
}

int main(int argc, char *argv[]) {
    cxxopts::Options options("DBLParse-core", "The core of DBLParse");
    options.allow_unrecognised_options();
    options.add_options()
        ("h,help", "Show help")
        ("download", "Download with url", cxxopts::value<std::string>())
        ("inflate", "Inflate file", cxxopts::value<std::string>())
        ;

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("download")) {
        const std::string url = result["download"].as<std::string>();
        dblp_download(url);
        return 0;
    }

    if (result.count("inflate")) {
        const std::string fileName = result["inflate"].as<std::string>();
        return dblp_inflate(fileName);
    }

    std::cout << options.help() << std::endl;
    return 0;
}
