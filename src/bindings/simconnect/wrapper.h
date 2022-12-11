#pragma once

#include <Windows.h>
#include <SimConnect.h>
#include <napi.h>

#include <list>
#include <map>

namespace msfs {
namespace simconnect {
    class Wrapper : public Napi::ObjectWrap<Wrapper> {
    private:
        struct DataDefinition {
            SIMCONNECT_CLIENT_DATA_DEFINITION_ID definitionId;
            DWORD offset;
            DWORD sizeOrType;
            float epsilon;
            Napi::String memberName;
        };

        HANDLE _simConnect;
        std::string _lastError;
        std::map<SIMCONNECT_CLIENT_DATA_ID, std::list<DataDefinition>> _clientDataAreas;

        bool clientDataIdExists(SIMCONNECT_CLIENT_DATA_ID clientDataId) const;

        void close();
    public:
        /**
         * @brief Constructs a new Wrapper object
         * @param info Parameter block for the Wrapper
         */
        Wrapper(const Napi::CallbackInfo& info);
        /**
         * @brief Destroys the Wrapper object
         */
        ~Wrapper();

        /**
         * @brief Opens a SimConnect connection to the server
         * @param info The callback block where the first element needs to be the client's name
         * @return Returns a Napi::Boolean and sets the last error, if the function returned false
         * @throw Excpetions if the arguments do not match
         */
        Napi::Value open(const Napi::CallbackInfo& info);
        /**
         * @brief Closes a SimConnect connection
         * @param info The parameter block without additional parameters
         */
        void close(const Napi::CallbackInfo& info);
        /**
         * @brief Creates a new client data area without registering it on the server
         * @param info The parameters with the client data ID
         * @return True, if the new ID is created, else false with the last error set
         */
        Napi::Value newClientDataArea(const Napi::CallbackInfo& info);
        /**
         * @brief Maps the client data name to the ID on the server
         * @param info The info block with the parameters for the clientDataName and the clientDataid
         * @return True if the mapping was successful, else false with the last error set
         */
        Napi::Value mapClientDataNameToId(const Napi::CallbackInfo& info);
        /**
         * @brief Adds a new client data definition
         * @param info The info block with parameters for the client data ID and the data definition
         * @return True if the definition is added, else false
         */
        Napi::Value addClientDataDefinition(const Napi::CallbackInfo& info);
        /**
         * @brief Creates anew client data area on the server
         * @param info The info block with the paramaters clientDataId, size and readOnly
         * @return True if the creation was successful, else false with the last error set
         */
        Napi::Value createClientDataArea(const Napi::CallbackInfo& info);
        /**
         * @brief Returns the last error of an other call
         * @param info The parameter block without additional parameters
         * @return Returns Napi::String with the last error
         */
        Napi::Value lastError(const Napi::CallbackInfo& info);

        /**
         * @brief Creates a new Wrapper object
         * @param info Parameter block for the new object
         * @return Returns the newly created object
         */
        static Napi::Value createNewItem(const Napi::CallbackInfo& info);
        /**
         * @brief Registers all binding functions in the JS environment
         * @param env The javascript environment
         * @param exports The collection of exported functions
         * @return The extended exported functions
         */
        static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    };
}
}
