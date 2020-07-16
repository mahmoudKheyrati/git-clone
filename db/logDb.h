#pragma once

#include "../core/Core.h"

struct LogEntry{
    String id;
    String title;
    String description;
    char date[30];
};

struct LogList{
    long size;
    long length;
    struct LogEntry* items;
};

struct LogList* getLogList(String path, String filename);
void saveLogList(struct LogList* list, String path, String filename);
void addLogEntry(struct LogList *list, struct LogEntry item) ;
void initLogList(struct LogList *list, int initSize);
void expandLogList(struct LogList *list);