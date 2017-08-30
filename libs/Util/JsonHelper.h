//
// Created by Friedemann Stoffregen on 26.04.17.
//

#ifndef SAMPLERV2_JSONHELPER_H
#define SAMPLERV2_JSONHELPER_H

#include <iostream>
#include <string>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <fstream>

using namespace std;
using namespace Poco::JSON;

class JsonHelper {
private:
    Object::Ptr JsonObject;
public:
    JsonHelper(char filename[]);

    Object::Ptr getObject(const char *key);

    Object::Ptr getObject(Object::Ptr object, const char *key);

    std::string getString(const char *key);

    std::string getString(Object::Ptr object, const char *key);

    int getInt(string key);

    int getInt(Object::Ptr object, string key);

    Poco::JSON::Array::Ptr getArray(string key);

    Poco::JSON::Array::Ptr getArray(Object::Ptr object, string key);
};


#endif //SAMPLERV2_JSONHELPER_H
