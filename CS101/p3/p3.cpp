#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Region::Region() {
    this->name = "No Name Set";
    this->viewers = 0;
    this->next = nullptr;
}

Region::Region(std::string name, int viewers, Region *next) {
    this->name = name;
    this->viewers = viewers;
    this->next = next;
}

Media::Media() {
    this->name = "No Name Set";
    this->next = nullptr;
    this->headRegionList = nullptr;
}

Media::Media(std::string name, Media *next) {
    this->name = name;
    this->next = next;
    this->headRegionList = nullptr;
}

MediaList::MediaList() {
    this->headMediaList = nullptr;
    this->count = 0;
}

int MediaList::getCount() {
    return this->count;
}

// print the specified media and its regions
// 1. return false and print nothing if the media is not in the list
// 2. otherwise return true and print the media and its regions
bool MediaList::printMedia(std::ostream &os, std::string name) {
    for (Media *cur = headMediaList; cur != nullptr; cur = cur->next) {
            if (cur->name == name) {
                os << "Media Name: " << name << endl;
                for (Region *cur2 = cur->headRegionList; cur2 != nullptr; cur2 = cur2->next) {
                    os << "    " << cur2->name << " | " << cur2->viewers << endl;
                }
                return true;
            }
    }
    return false;
}

// print all media and their regions
// print nothing if the list is empty
void MediaList::print(std::ostream &os) {
    for (Media *cur = headMediaList; cur != nullptr; cur = cur->next) {
        os << "Media Name: " << cur->name << endl;
        for (Region *cur2 = cur->headRegionList; cur2 != nullptr; cur2 = cur2->next) {
            os << "    " << cur2->name << " | " << cur2->viewers << endl;
        }
    }
}

// add the media to the back of the list
// 1. return false and do nothing if the media is already in the list
// 2. otherwise return true and add the media to the back of the list
// - do not forget to update count
bool MediaList::addMedia(std::string name) {
    Media *x = new Media(name);
    if (headMediaList == nullptr) {
        headMediaList = x;
        this->count += 1;
        return true;
    }
    if (headMediaList->name == name) {
        return false;
    }
    Media *last = headMediaList;
    while (last->next != nullptr) {
        if (last->name == name) {
            return false;
        }
        last = last->next;
    }
    if (last->name == name) {
        return false;
    }
    last->next = x;
    this->count += 1;
    return true;
}

// add the region to the back of the media's region list
// 1. return false and do nothing if the media is not in the list
// 2. if the regionName is already in the region list, update the viewers and return true
// 3. otherwise add the region to the back of the media's list and return true
bool MediaList::addRegion(std::string mediaName, std::string regionName, int viewers) {
    Region *x = new Region(regionName, viewers);
    for (Media *cur = headMediaList; cur != nullptr; cur = cur->next) {
        if (cur->name == mediaName) {
            if (cur->headRegionList == nullptr) {
                cur->headRegionList = x;
                return true;
            }
            if (cur->headRegionList->name == regionName) {
                cur->headRegionList->viewers = viewers;
                return true;
            }
            Region *last = cur->headRegionList;
            while (last->next != nullptr) {
                if (last->name == regionName) {
                    last->viewers = viewers;
                    return true;
                }
                last = last->next;
            }
            if (last->name == regionName) {
                last->viewers = viewers;
                return true;
            }
            last->next = x;
            return true;
        }
    }
    return false;
}

// add the media to the list in ascending order by name
// 1. return false and do nothing if the media is already in the list
// 2. otherwise return true and add the media to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
bool MediaList::addMediaOrdered(std::string name) {
    Media *x = new Media(name);
    if (headMediaList == nullptr) {
        headMediaList = x;
        this->count += 1;
        return true;
    }
    if (headMediaList->name == name) {
        return false;
    }
    if (x->name < headMediaList->name) {
        x->next = headMediaList;
        headMediaList = x;
        this->count += 1;
        return true;
    }
    Media *prev = headMediaList;
    Media *cur = headMediaList->next;
    while (cur != nullptr) {
        if (cur->name == name) {
            return false;
        }
        if (x->name < cur->name) break;
        prev = prev->next;
        cur = cur->next;
    }
    prev->next = x;
    x->next = cur;
    this->count += 1;
    return true;
}

// add the region to the media's region list in descending order by viewers
// 1. return false and do nothing if the media is not in the list
// 2. if the regionName is already in the region list, update the viewers and return true
// 3. otherwise add the region to the media's list and return true
bool MediaList::addRegionOrdered(std::string mediaName, std::string regionName, int viewers) {
    Region *x = new Region(regionName, viewers);
    for (Media *cur = headMediaList; cur != nullptr; cur = cur->next) {
        if (cur->name == mediaName) {
            if (cur->headRegionList == nullptr) {
                cur->headRegionList = x;
                return true;
            }
            if (cur->headRegionList->name == regionName) {
                cur->headRegionList->viewers = viewers;
                return true;
            }
            if (x->viewers > cur->headRegionList->viewers) {
                x->next = cur->headRegionList;
                cur->headRegionList = x;
                return true;
            }
            Region *prev = cur->headRegionList;
            Region *cur2 = cur->headRegionList->next;
            while (cur2 != nullptr) {
                if (cur2->name == regionName) {
                    cur2->viewers = viewers;
                    return true;
                }
                if (x->viewers > cur2->viewers) break;
                prev = prev->next;
                cur2 = cur2->next;
            }
            prev->next = x;
            x->next = cur2;
            return true;
        }
    }
    return false;
}

// remove the media and its regions from the list
// 1. return false and do nothing if the media is not in the list
// 2. otherwise return true and remove the media and its regions
// - do not forget to update count
bool MediaList::removeMedia(std::string name) {
    if (headMediaList == nullptr) {
        return false;
    }
    if (name == headMediaList->name) {
        Media *tbd = headMediaList;
        headMediaList = headMediaList->next;
        delete tbd;
        this->count -= 1;
        return true;
    }
    Media *prev = headMediaList;
    for (Media *cur = headMediaList->next; cur != nullptr; cur = cur->next) {
        if (cur->name == name) {
            prev->next = cur->next;
            delete cur;
            this->count -= 1;
            return true;
        }
        prev = prev->next;
    }
    return false;
}

// remove the region from the media's region list
// 1. return false and do nothing if the media is not in the list
// 2. return false and do nothing if the region is not in the media's region list
// 3. otherwise return true and remove the region from the media's list
bool MediaList::removeRegion(std::string mediaName, std::string regionName) {
    if (headMediaList == nullptr) {
        return false;
    }
    if (mediaName == headMediaList->name) {
        if (headMediaList->headRegionList == nullptr) {
            return false;
        }
        if (regionName == headMediaList->headRegionList->name) {
                Region *tbd = headMediaList->headRegionList;
                headMediaList->headRegionList = headMediaList->headRegionList->next;
                delete tbd;
                return true;
            }
            Region *prev = headMediaList->headRegionList;
            for (Region *cur2 = headMediaList->headRegionList->next; cur2 != nullptr; cur2 = cur2->next) {
                if (cur2->name == regionName) {
                    prev->next = cur2->next;
                    delete cur2;
                    return true;
                }
                prev = prev->next;
            }
    }
    for (Media *cur = headMediaList->next; cur != nullptr; cur = cur->next) {
        if (cur->name == mediaName) {
            if (regionName == cur->headRegionList->name) {
                Region *tbd = cur->headRegionList;
                cur->headRegionList = cur->headRegionList->next;
                delete tbd;
                return true;
            }
            Region *prev = cur->headRegionList;
            for (Region *cur2 = cur->headRegionList->next; cur2 != nullptr; cur2 = cur2->next) {
                if (cur2->name == regionName) {
                    prev->next = cur2->next;
                    delete cur2;
                    return true;
                }
                prev = prev->next;
            }
        }
    }
    return false;
}

// destroy the list by removing all media and their regions
MediaList::~MediaList() {
    while (headMediaList != nullptr) {
            Media *toBeDeleted = headMediaList;
            while (headMediaList->headRegionList != nullptr) {
                Region *tbd2 = headMediaList->headRegionList;
                headMediaList->headRegionList = headMediaList->headRegionList->next;
                delete tbd2;
            }
            headMediaList = headMediaList->next;
            delete toBeDeleted;
    }
}

// deep copy the source list
// - do not forget to update count
MediaList::MediaList(const MediaList &src) {
    headMediaList = nullptr;
    count = src.count;
    for (Media *cur = src.headMediaList; cur != nullptr; cur = cur->next) {
        addMedia(cur->name);
        for (Region *cur2 = cur->headRegionList; cur2 != nullptr; cur2 = cur2->next) {
            addRegion(cur->name, cur2->name, cur2->viewers); 
        }
    }
}

// remove all media and their regions then deep copy the source list
// - do not forget to update count
const MediaList &MediaList::operator=(const MediaList &src) {
    if (this != &src) {
        while (headMediaList != nullptr) {
            Media *toBeDeleted = headMediaList;
            headMediaList = headMediaList->next;
            delete toBeDeleted;
        }
        for (Media *cur = src.headMediaList; cur != nullptr; cur = cur->next) {
            count = src.count;
            addMedia(cur->name);
            for (Region *cur2 = cur->headRegionList; cur2 != nullptr; cur2 = cur2->next) {
                addRegion(cur->name, cur2->name, cur2->viewers); 
            }
        }
    }
    return *this;
}
