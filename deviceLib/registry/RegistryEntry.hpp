#ifndef UCL_REGISTRY_ENTRY_HPP
#define UCL_REGISTRY_ENTRY_HPP

#include <string>
#include <vector>
#include <map>

#include "../crypto/crypto.hpp"
#include "../json/ArduinoJson.hpp"
using namespace ArduinoJson;
using namespace std;

enum RegistryEntryType {
    UPSERT,
    DELETE
};

class RegistryEntry {
    string getSignatureText();

public:

    // Metadata
    UUID uuid;
    SIGNATURE_T signature;
    PUB_HASH_T publicKeyUsed;
    RegistryEntryType type;

    // Content
    string key;
    string value;

    // Functions
    RegistryEntry(RegistryEntryType type, string key, string value, Crypto::asymmetric::KeyPair pair);

    RegistryEntry(string serializedEntry);

    enum Verify {
        OK,
        PubKeyNotFound,
        SignatureInvalid
    };

    Verify verifySignature(map<PUB_HASH_T, PUBLIC_KEY_T> keys);

    string serialize();
};


#endif //UCL_REGISTRY_ENTRY_HPP
