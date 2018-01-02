/* spider.h --- 
 * Filename: spider.h
 * Created: Tue Jan  2 13:11:39 2018 (+0800)
 */

/* Copyright Hamlet_Jiaxiaoyu.
 * 
 * 允许免费使用，拷贝，修改，发布，但在所有的拷贝上必须保留上述
 * copyright部分和本使用声明部分，除非显示声明，copyright的持有者
 * 不得作为再发布软件的广告。copyright的持有者对使用本软件的适用范围不做任何声明，
 * 
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
#ifndef _SPIDER_H_
#define _SPIDER_H_

#include "curl/curl.h"
#include "include/json/json.h"


class Spider
{
public:
    const static int MAX_BUFF = 1024 * 512;
    Spider();
    virtual ~Spider();
    bool init_env();

    CURLcode json_spider(char* url, size_t max_len);

    static void* start_spider_thread(void* param);

    static size_t write_json_data(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t write_pic_data(void* ptr, size_t size, size_t nmemb, void* stream);

    void reset_data_shift();

    void pic_spider(const char* pic);

    void do_spider();

private:
    int get_buff_shift()
    {
        return m_data_shift;
    }

    void shift_buff(int shift)
    {
        m_data_shift += shift;
    }

    char* get_buff_ptr()
    {
        return m_buff;
    }

    void init_header();

    CURLcode perform();

    FILE* open_new_file(const char* path);

    FILE* get_open_file()
    {
        return m_file;
    }

    const char* parse_base_json();
    void parse_photo_json();
    void parse_space_json();

private:
    struct curl_slist* m_headers;
    CURL* m_json_curl;
    CURL* m_pic_curl;

    char m_buff[MAX_BUFF];
    int m_data_shift;
    int m_target_id;
    FILE* m_file;
    bool m_is_pic;

    Json::Value m_root;
    Json::Reader m_reader;
    
};//class spider

#endif // _SPIDER_H_
