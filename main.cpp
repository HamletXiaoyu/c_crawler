// main.cpp --- 
// Filename: main.cpp
// Created: Tue Jan  2 13:22:21 2018 (+0800)
// 
// 
// Copyright Hamlet_Jiaxiaoyu.
// 
// 允许免费使用，拷贝，修改，发布，但在所有的拷贝上必须保留上述
// copyright部分和本使用声明部分，除非显示声明，copyright的持有者
// 不得作为再发布软件的广告。copyright的持有者对使用本软件的适用范围不做任何声明，
// 
// THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
// INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
// EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
// DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
// TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
// 
// 

#include "spider.h"
#include "global.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief show the usage of spider
 */
void usage()
{
    fprintf(stderr, "Usage:\nspider -t thread_count -p save_path -i start_id\n");
}

/**
 * @brief start threads
 */
int start_threads(int cnt)
{
    if(cnt <= 0)
        return 1;
    
    pthread_t *pid = new pthread_t[cnt];
    for(int j = 0; j < cnt; ++j){
        if(pthread_create(&pid[j], NULL, Spider::start_spider_thread, NULL)){
            fprintf(stderr, "Create sever thread failed.\n");
            return 1;
        }
    }
    for(int j = 0; j < cnt; ++j){
        pthread_join(pid[j], NULL);
    }
    delete []pid;
    
    return 0;
}

int main(int argc, const char* argv[])
{
    if(argc != 7){
        usage();
        return 1;
    }

    int thread_cnt = 0;
    const char* path = NULL;
    int start_id = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (i % 2 == 0 || i + 1 >= argc) continue;

        if (strncmp(argv[i], "-t", 2) == 0)
        {
            thread_cnt = atoi(argv[i + 1]);
            continue;
        }

        if (strncmp(argv[i], "-p", 2) == 0)
        {
            path = argv[i + 1];
            continue;
        }

        if (strncmp(argv[i], "-i", 2) == 0)
        {
            start_id = atoi(argv[i + 1]);
            continue;
        }
    }

    if (thread_cnt <= 0 || start_id <= 0 || !path || path[0] == '\0')
    {
        usage();
        return 1;
    }

    Global* g = Global::get_instance();
    if (!g->set_path(path))
    {
        delete g;
        return 1;
    }

    g->set_target_start(start_id);
    g->init_global_env();

    start_threads(thread_cnt);

    delete g;
    
    return 0;
}

    
