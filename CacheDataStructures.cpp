#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <cstdlib>
#include <time.h>
#include "getContent.c"

using namespace std;

#define MAX_CACHE_SIZE 350*1024

/*
PRP: 1 = FIFO, 2 = RANDOM, 3 = MAXS
*/
#define PRP 2

/*
Uncomment FIFO when PRP is 1
Uncomment MAXS when PRP is 3
*/

//#define FIFO
//#define MAXS

class Page {
    public:
    string data;
    string url;
    int size_of_page;

    public: Page (string url, string data, int size_of_page) {
        this->url = url;
        this->data = data;
        this->size_of_page = size_of_page;
    }

    public: Page () {
    }

    public: ~Page (){ 
    }
};

#ifdef MAXS
typedef struct page_size_index {
    int page_size;
    int index;
} size_index;

class ComparePages {
    public:
        bool operator () (size_index s1, size_index s2){
            if (s1.page_size >= s2.page_size)
                return true;
            else false;
        }
};
#endif

class Cache {
    public:
    std::vector<Page> cache_data;
    int size_of_cache = 0;
    int cache_hits = 0, cache_misses = 0;
    long total_bytes_fetched = 0, cache_hit_bytes = 0;

#ifdef FIFO
    std::queue<int> vector_indices;
#endif

    std::map<string, int> url_to_index;

#ifdef MAXS
    std::priority_queue<size_index, vector<size_index>, ComparePages> pq_indices;
#endif

    int add_page (Page page) {
        if (size_of_cache + page.size_of_page <= MAX_CACHE_SIZE){
            cache_data.push_back(page);
// printf("page added to Cache successfully\n");
// printf("Index in Cache is %d\n", (int)(cache_data.size()-1));
            url_to_index[page.url] = cache_data.size()-1;
// printf("url is mapped to index\n");
#ifdef FIFO
            vector_indices.push(cache_data.size()-1);
#endif

#ifdef MAXS         
            size_index pq_entry;
            pq_entry.page_size = page.size_of_page;
            pq_entry.index = (int) (cache_data.size() - 1);
            pq_indices.push(pq_entry);
// printf("Pushing into PQ\n");
#endif

            size_of_cache = size_of_cache + page.size_of_page;
// cout << "Step 2" << endl;
        }
        else {
// printf ("No free space. Need to remove some pages from Cache.\n");
            /* Get list of indices of pages to be removed based on
               the Page Replacement Policy. */
            if (page.size_of_page > MAX_CACHE_SIZE) {
                cout << "Cache Capacity insufficient. Cannot cache WebPage" << endl;
                return 0;
            }
            std::list<int> list_of_indices = pages_to_remove(PRP, page.size_of_page);
// printf("Pages to remove determined successfully\n");
            int freed_size = 0;

            // Remove pages from cache that were selected to be replaced.
            for (std::list<int>::iterator it = list_of_indices.begin(); it !=list_of_indices.end(); it++) {
                freed_size = freed_size + remove_page(*it);
            }
// printf("Pages removed successfully\n");

            // Add Page to Vector
            cache_data.push_back(page);
            // Add Page to URL-Index Map
            url_to_index[page.url] = cache_data.size() - 1;

#ifdef FIFO
            // Add Page to Queue
            vector_indices.push(cache_data.size()-1);
#endif

#ifdef MAXS
            // Add Page to Priority Queue
            size_index pq_entry;
            pq_entry.page_size = page.size_of_page;
            pq_entry.index = cache_data.size() - 1;
// printf("Pushing into PQ\n");
            pq_indices.push(pq_entry);
#endif

        }
        return cache_data.size()-1;
    }

    /* 
    search the map for url and get the index in vector.
    fetch the data from vector using the index.
    post the data to client.
    if not in the cache then fetch using Curl and post to client
    and add to cache. */
    string search_page (string url){
        std::map<string, int>::iterator it;
        if ((it = url_to_index.find(url)) != url_to_index.end()) {
            cache_hit_bytes = cache_hit_bytes + cache_data[it->second].size_of_page;
            cout << "Number of Cache Hits: " << ++cache_hits << "\n Byte Hits in Cache: "<< cache_hit_bytes << endl;
            return cache_data[it->second].data;
        } else {
            char *url_str = new char[url.size() + 1];
            char *body_str;
            std::copy(url.begin(), url.end(), url_str);
            url_str[url.size()] = '\0';
            body_str = getContent(url_str);
// printf("getContent successfully returned\n");
            string body(body_str);
// printf("Size of Body: %d\n", (int)body.size());
            // Add Page to Cache and update Queue
            Page page(url, body, (int)body.size());
// printf("page created successfully\n");
            add_page (page);
            total_bytes_fetched = total_bytes_fetched + page.size_of_page;
            cout << "Number of Cache Misses: " << ++cache_misses << "\n Total Bytes Fetched from Web: " << total_bytes_fetched << endl;
            return body;
        }            
    }

    int remove_page (int index) {
        int size_freed = cache_data[index].size_of_page;
        size_of_cache = size_of_cache - size_freed;

        // Remove from Map
        url_to_index.erase(cache_data[index].url);

        // Remove from Cache
        cache_data[index].data = '\0';
        cache_data[index].url = '\0';
        cache_data[index].size_of_page = 0;
// cout << "Page Removed" << endl;    
        return size_freed;
    }
    
    std::list<int> pages_to_remove (int i, int size_of_page) {
        std::list<int> pages_to_remove;
        int space_freed = MAX_CACHE_SIZE - size_of_cache;
        if (i == 1) {
            // FIFO
#ifdef FIFO
            do{
// printf("Trying to free space\n");
                space_freed = space_freed + cache_data[vector_indices.front()].size_of_page;
                pages_to_remove.push_back(vector_indices.front());
// printf("Added to Paged_To_Remove List\n");
                vector_indices.pop();
// printf("Removed from Queue\n");
            } while (space_freed < size_of_page);
#endif
        } else if (i == 2) {
            // RANDOM
            srand(time(NULL));
            int size = cache_data.size();
            do {
                // printf("In Random\n");
                int i = rand() % size;
                space_freed = space_freed + cache_data[i].size_of_page;
                pages_to_remove.push_back(i);
            } while (space_freed < size_of_page);
        } else if (i == 3) {
            // MAXS - Remove the largest entry first.
#ifdef MAXS
            do {
                // printf(" In MAXS\n");
                space_freed = space_freed + pq_indices.top().page_size;
                pages_to_remove.push_back(pq_indices.top().index);
// printf("Space freed is: %d\n", space_freed);
                pq_indices.pop();
// printf("Popped from PQ\n");
            } while (space_freed < size_of_page);
#endif
        }
        return pages_to_remove;
        
    }
};
