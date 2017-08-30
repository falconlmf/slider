#include "ram.h"
#include "const.h"

void jsonControl(char *json, byte jsonLen) {
    JsonParser<32> parser;
    JsonHashTable hashTable = parser.parseHashTable(json);

    if(!hashTable.success()) {
    	debugmln("json fail");
    } else {
    	debugmln("json ok");
    }
}