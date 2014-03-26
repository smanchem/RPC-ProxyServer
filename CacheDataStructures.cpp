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

#define MAX_SIZE 220*1024

#define PRP 2

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

class Cache {
    public:
    std::vector<Page> cache_data;
    int size_of_cache = 0;
    std::queue<int> vector_indices;
    std::map<string, int> url_to_index;

    int add_page (Page page) {
        if (size_of_cache + page.size_of_page <= MAX_SIZE){
            cache_data.push_back(page);
printf("page added to Cache successfully\n");
printf("Index in Cache is %d\n", cache_data.size()-1);
            url_to_index[page.url] = cache_data.size()-1;
printf("url is mapped to index\n");
            vector_indices.push(cache_data.size()-1);
cout << "Step 2" << endl;
        }
        else {
printf ("here\n");
            /* Get list of indices of pages to be removed based on
               the Page Replacement Policy. */
            if (page.size_of_page > MAX_SIZE) {
                cout << "Cache Capacity insufficient. Cannot fetch WebPage" << endl;
                exit(0);
            }
            std::list<int> list_of_indices = pages_to_remove(PRP, page.size_of_page);
printf("Pages to remove determined successfully\n");
            int freed_size = 0;

            // Remove pages from cache that were selected to be replaced.
            for (std::list<int>::iterator it = list_of_indices.begin(); it !=list_of_indices.end(); it++) {
                freed_size = freed_size + remove_page(*it);
            }
printf("Pages removed successfully\n");
            if (freed_size < page.size_of_page) {
                cout << "Cache Capacity insufficient" << endl;
                exit(0);
            }
            // Add Page to Vector
            cache_data.push_back(page);
            // Add Page to URL-Index Map
            url_to_index[page.url] = cache_data.size() - 1;
            // Add Page to Queue
            vector_indices.push(cache_data.size()-1);
        }
        return cache_data.size()-1;
    }

    string search_page (string url){
        // search the hash map for url and get the index in vector.
        // fetch the data from vector using the index.
        // post the data to client
        // if not in the cache then fetch using Curl and post to client
        //    and add to cache.
        std::map<string, int>::iterator it;
        if ((it = url_to_index.find(url)) != url_to_index.end()) {
            return cache_data[it->second].data;
        } else {
            char *url_str = new char[url.size() + 1];
            char *body_str;
            std::copy(url.begin(), url.end(), url_str);
            url_str[url.size()] = '\0';
            body_str = getContent(url_str);
printf("getContent successfully returned\n");
            string body(body_str);
cout << "Step 1" << endl;
printf("Size of Body: %d\n", (int)body.size());
            // Add Page to Cache and update Queue
            Page page(url, body, (int)body.size());
printf("page created successfully\n");
            add_page (page);
cout << "Step 3" << endl;
            return body;
        }            
    }

    int remove_page (int index) {
        int size_freed = cache_data[index].size_of_page;

        // Remove from Map
        url_to_index.erase(cache_data[index].url);

        // Remove from Cache
        cache_data[index].data = '\0';
        cache_data[index].url = '\0';
        cache_data[index].size_of_page = 0;
cout << "Page Removed" << endl;    
        return size_freed;
    }
    
    std::list<int> pages_to_remove (int i, int size_of_page) {
        // For FIFO - Queue
        //  Have a global variable of size initialized to zero.
            //  Fetch size of topmost page and then remove topmost page.
           //  global_size = global_size + size_of_topmost_page; -- do this till global_size >= size_of_page
       // For Random - Queue
            // Generate a random index within the range of vector indices and remove that page. Check size freed and size requried.
        // For LRU - Priority Queue
        std::list<int> pages_to_remove;
        int space_freed = 0;
        if (i == 1) {
            // FIFO        
            do{
printf("Trying to free space\n");
printf("Index of front of queue is: %d\n", vector_indices.front());

                space_freed = space_freed + cache_data[vector_indices.front()].size_of_page;
                pages_to_remove.push_back(vector_indices.front());
printf("Added to Paged_To_Remove List\n");
                vector_indices.pop();
printf("Removed from Queue\n");
            } while (space_freed < size_of_page);
        } else if (i == 2) {
            // RANDOM
            srand(time(NULL));
            int size = cache_data.size()-1;
            do {
                printf("In Random\n");
                int i = rand() % size;
                space_freed = space_freed + cache_data[i].size_of_page;
                pages_to_remove.push_back(i);
            } while (space_freed < size_of_page);
        }         
        return pages_to_remove;
        
    }
};
