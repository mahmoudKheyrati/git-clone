#pragma once

#include "../core/Core.h"

struct LogEntry{
    char id[40];
    char title[100];
    char description[100];
    char date[40];
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