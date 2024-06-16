#ifdef ENABLE_REMOTE_CONTROL

#include "GameInteractor.h"
#include <spdlog/spdlog.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <unordered_map>
#include <tuple>
#include <type_traits>
#include <libultraship/libultraship.h>
#include <zlib.h>

// MARK: - Remote

void GameInteractor::EnableRemoteInteractor() {
    if (isRemoteInteractorEnabled) {
        return;
    }

    if (SDLNet_ResolveHost(&remoteIP, CVarGetString("gRemote.IP", "127.0.0.1"), CVarGetInteger("gRemote.Port", 43384)) == -1) {
        SPDLOG_ERROR("[GameInteractor] SDLNet_ResolveHost: {}", SDLNet_GetError());
    }

    isRemoteInteractorEnabled = true;

    // First check if there is a thread running, if so, join it
    if (remoteThreadReceive.joinable()) {
        remoteThreadReceive.join();
    }

    remoteThreadReceive = std::thread(&GameInteractor::ReceiveFromServer, this);
}

/**
 * Raw data handler
 * 
 * If you are developing a new remote, you should probably use the json methods instead. This 
 * method requires you to parse the data and ensure packets are complete manually, we cannot
 * gaurentee that the data will be complete, or that it will only contain one packet with this
 */
void GameInteractor::RegisterRemoteDataHandler(std::function<void(char payload[512])> method) {
    remoteDataHandler = method;
}

/**
 * Json handler
 * 
 * This method will be called when a complete json packet is received. All json packets must
 * be delimited by a null terminator (\0).
 */
void GameInteractor::RegisterRemoteJsonHandler(std::function<void(nlohmann::json)> method) {
    remoteJsonHandler = method;
}

void GameInteractor::RegisterRemoteConnectedHandler(std::function<void()> method) {
    remoteConnectedHandler = method;
}

void GameInteractor::RegisterRemoteDisconnectedHandler(std::function<void()> method) {
    remoteDisconnectedHandler = method;
}

void GameInteractor::DisableRemoteInteractor() {
    if (!isRemoteInteractorEnabled) {
        return;
    }

    isRemoteInteractorEnabled = false;
    remoteThreadReceive.join();
    remoteDataHandler = nullptr;
    remoteJsonHandler = nullptr;
    remoteConnectedHandler = nullptr;
    remoteDisconnectedHandler = nullptr;
}

void GameInteractor::TransmitDataToRemote(const char* payload) {
    SDLNet_TCP_Send(remoteSocket, payload, strlen(payload) + 1);
}

// Appends a newline character to the end of the json payload and sends it to the remote
void GameInteractor::TransmitJsonToRemote(nlohmann::json payload) {
    
    if(strlen(payload.dump().c_str()) < 100 || payload.contains("jointTable")){
        TransmitDataToRemote(payload.dump().c_str());
    } else{
        //convert the json to string 
        char uncomp[50000];
        char comp[10000];
        //char ununcomp[50000];

        strcpy(uncomp, payload.dump().c_str());

        SPDLOG_INFO("[GameInteractor] Original Payload:\n{}", uncomp);

        //compress
        // zlib struct
        z_stream defstream;
        defstream.zalloc = Z_NULL;
        defstream.zfree = Z_NULL;
        defstream.opaque = Z_NULL;

        defstream.avail_in = (uInt)strlen(uncomp); // size of input, string + terminator
        defstream.next_in = (Bytef *)uncomp; // input char array
        defstream.avail_out = (uInt)sizeof(comp); // size of output
        defstream.next_out = (Bytef *)comp; // output char array

        //deflateInit2(&defstream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY);
        deflateInit(&defstream, Z_DEFAULT_COMPRESSION);
        deflate(&defstream, Z_FINISH);
        int result = deflateEnd(&defstream);

        SPDLOG_INFO("[GameInteractor] Compressed Payload:\n{}", comp);

        
        //decompress
        // z_stream infstream;
        // infstream.zalloc = Z_NULL;
        // infstream.zfree = Z_NULL;
        // infstream.opaque = Z_NULL;

        // infstream.avail_in = (uInt)((char*)defstream.next_out - comp); // size of input
        // infstream.next_in = (Bytef *)comp; // input char array
        // infstream.avail_out = (uInt)sizeof(ununcomp); // size of output
        // infstream.next_out = (Bytef *)ununcomp; // output char array

        // inflateInit(&infstream);
        // //inflateInit2(&infstream, 15);
        // inflate(&infstream, Z_NO_FLUSH);
        // inflateEnd(&infstream);

        // SPDLOG_INFO("[GameInteractor] Uncompressed Payload:\n{}", ununcomp);

        // if(strcmp(uncomp, ununcomp) == 0){
        //     SPDLOG_INFO("Original And Uncompressed Matched!");
        // }
        if(result == Z_OK){
            TransmitDataToRemote(comp);
        }
    }
}

// MARK: - Private

std::string receivedData;

void GameInteractor::ReceiveFromServer() {
    while (isRemoteInteractorEnabled) {
        while (!isRemoteInteractorConnected && isRemoteInteractorEnabled) {
            //SPDLOG_TRACE("[GameInteractor] Attempting to make connection to server...");
            remoteSocket = SDLNet_TCP_Open(&remoteIP);

            if (remoteSocket) {
                isRemoteInteractorConnected = true;
                SPDLOG_INFO("[GameInteractor] Connection to server established!");

                if (remoteConnectedHandler) {
                    remoteConnectedHandler();
                }
                break;
            }
        }

        SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
        if (remoteSocket) {
            SDLNet_TCP_AddSocket(socketSet, remoteSocket);
        }

        // Listen to socket messages
        while (isRemoteInteractorConnected && remoteSocket && isRemoteInteractorEnabled) {
            // we check first if socket has data, to not block in the TCP_Recv
            int socketsReady = SDLNet_CheckSockets(socketSet, 0);

            if (socketsReady == -1) {
                SPDLOG_ERROR("[GameInteractor] SDLNet_CheckSockets: {}", SDLNet_GetError());
                break;
            }

            if (socketsReady == 0) {
                continue;
            }
            
            char remoteDataReceived[512];
            memset(remoteDataReceived, 0, sizeof(remoteDataReceived));
            int len = SDLNet_TCP_Recv(remoteSocket, &remoteDataReceived, sizeof(remoteDataReceived));
            if (!len || !remoteSocket || len == -1) {
                SPDLOG_ERROR("[GameInteractor] SDLNet_TCP_Recv: {}", SDLNet_GetError());
                break;
            }

            HandleRemoteData(remoteDataReceived);

            receivedData.append(remoteDataReceived, len);
            // char remoteDataReceived[512];
            // char inflatedDataReceived[512];
            // memset(remoteDataReceived, 0, sizeof(remoteDataReceived));
            // uLong compSize = SDLNet_TCP_Recv(remoteSocket, &remoteDataReceived, sizeof(remoteDataReceived));
            // uLong ucompSize = sizeof(remoteDataReceived);

            // uncompress((Bytef *) inflatedDataReceived, &ucompSize, (Bytef *) remoteDataReceived, compSize);

            // SPDLOG_INFO("[GameInteractor] Recieved uncompressed payload:\n{}", inflatedDataReceived);

            // SPDLOG_INFO("[GameInteractor] Recieved compressed payload:\n{}", remoteDataReceived);

            // int len = sizeof(inflatedDataReceived);

            // // char remoteDataReceived[512];
            // // memset(remoteDataReceived, 0, sizeof(remoteDataReceived));
            // // int len = SDLNet_TCP_Recv(remoteSocket, &remoteDataReceived, sizeof(remoteDataReceived));
            // if (!len || !remoteSocket || len == -1) {
            //     SPDLOG_ERROR("[GameInteractor] SDLNet_TCP_Recv: {}", SDLNet_GetError());
            //     break;
            // }

            // HandleRemoteData(inflatedDataReceived);

            // receivedData.append(inflatedDataReceived, len);

            // Proess all complete packets
            size_t delimiterPos = receivedData.find('\0');
            while (delimiterPos != std::string::npos) {
                // Extract the complete packet until the delimiter
                std::string packet = receivedData.substr(0, delimiterPos);
                // Remove the packet (including the delimiter) from the received data
                receivedData.erase(0, delimiterPos + 1);
                HandleRemoteJson(packet);
                // Find the next delimiter
                delimiterPos = receivedData.find('\0');
            }
        }

        if (isRemoteInteractorConnected) {
            SDLNet_TCP_Close(remoteSocket);
            isRemoteInteractorConnected = false;
            if (remoteDisconnectedHandler) {
                remoteDisconnectedHandler();
            }
            SPDLOG_INFO("[GameInteractor] Ending receiving thread...");
        }
    }
}

void GameInteractor::HandleRemoteData(char payload[512]) {
    if (remoteDataHandler) {
        remoteDataHandler(payload);
        return;
    }
}

void GameInteractor::HandleRemoteJson(std::string payload) {
    nlohmann::json jsonPayload;
    try {
        jsonPayload = nlohmann::json::parse(payload);
    } catch (const std::exception& e) {
        SPDLOG_ERROR("[GameInteractor] Failed to parse json: \n{}\n{}\n", payload, e.what());
        return;
    }

    if (remoteJsonHandler) {
        remoteJsonHandler(jsonPayload);
        return;
    }
}

#endif
