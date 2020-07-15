#pragma once

#include "FileHelper.h"
#include "Macros.h"
#include "string.h"
#include "stdio.h"
#include "hasher.h"


String getDate();

long int getCurrentTime();

String rangeSelect(String string , int start , int end);

String strConcat(String list[], int size);
