//
// Created by Friedemann Stoffregen on 26.04.17.
//

#include "JsonHelper.h"

JsonHelper::JsonHelper(char *filename) {
    string line;
    string content = "";
    Parser loParser;

    ifstream configFile(filename);
    if (configFile.is_open()) {
        while (getline(configFile, line)) {
            content.append(line);
        }
        configFile.close();
    }

    // Parse the JSON and get the Results
    //
    Poco::Dynamic::Var loParsedJson = loParser.parse(content);
    Poco::Dynamic::Var loParsedJsonResult = loParser.result();

    this->JsonObject = loParsedJsonResult.extract<Object::Ptr>();


    std::vector<std::string> keys;
}

Object::Ptr JsonHelper::getObject(const char *key) {
    Object::Ptr aoJsonObject = this->JsonObject;
    return this->getObject(aoJsonObject, key);
}

Object::Ptr JsonHelper::getObject(Object::Ptr object, const char *key) {
    Poco::Dynamic::Var loVariable;
    Object::Ptr ret;
    loVariable = object->get(key);
    return loVariable.extract<Object::Ptr>();
}

string JsonHelper::getString(const char *key) {
    return getString(this->JsonObject, key);

}

string JsonHelper::getString(Object::Ptr object, const char *key) {
    Poco::Dynamic::Var loVariable;
    string lsReturn;
    string lsKey(key);

    // Get the member Variable
    //
    std::vector<std::string> names;
    loVariable = object->get(lsKey);
    object->getNames(names);
    // Get the Value from the Variable
    //
    lsReturn = loVariable.convert<std::string>();
    return lsReturn;
}

int JsonHelper::getInt(Object::Ptr object, string key) {
    Poco::Dynamic::Var loVariable;
    int lsReturn;
    string lsKey(key);

    // Get the member Variable
    //
    std::vector<std::string> names;
    loVariable = object->get(lsKey);
    object->getNames(names);
    // Get the Value from the Variable
    //
    lsReturn = loVariable.convert<int>();

    return lsReturn;
}

int JsonHelper::getInt(string key) {
    return getInt(JsonObject, key);
}

Poco::JSON::Array::Ptr JsonHelper::getArray(string key) {
    return getArray(JsonObject, key);
}

Poco::JSON::Array::Ptr JsonHelper::getArray(Object::Ptr object, string key) {
    Poco::Dynamic::Var loVariable;
    Object::Ptr ret;
    loVariable = object->get(key);
    return loVariable.extract<Array::Ptr>();
}

