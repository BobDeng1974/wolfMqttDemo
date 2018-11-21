
#ifndef WOLFMQTT_SOCKET_H
#define WOLFMQTT_SOCKET_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "mqtt_types.h"
#ifdef ENABLE_MQTT_TLS
    #if !defined(WOLFSSL_USER_SETTINGS) && !defined(USE_WINDOWS_API)
        #include <options.h>
    #endif
	#include <wolfssl/wolfcrypt/settings.h>
    #include <wolfssl/ssl.h>
    #include <wolfssl/wolfcrypt/types.h>

    #ifndef WOLF_TLS_DHKEY_BITS_MIN /* allow define to be overridden */
        #ifdef WOLFSSL_MAX_STRENGTH
            #define WOLF_TLS_DHKEY_BITS_MIN 2048
        #else
            #define WOLF_TLS_DHKEY_BITS_MIN 1024
        #endif
    #endif
#endif

/* Default Port Numbers */
#define MQTT_DEFAULT_PORT   1883
#define MQTT_SECURE_PORT    8883


struct _MqttClient;

/* Function callbacks */
typedef int (*MqttTlsCb)(struct _MqttClient* client);

typedef int (*MqttNetConnectCb)(void *context,
    const char* host, word16 port, int timeout_ms);
typedef int (*MqttNetWriteCb)(void *context,
    const byte* buf, int buf_len, int timeout_ms);
typedef int (*MqttNetReadCb)(void *context,
    byte* buf, int buf_len, int timeout_ms);
#ifdef WOLFMQTT_SN
typedef int (*MqttNetPeekCb)(void *context,
    byte* buf, int buf_len, int timeout_ms);
#endif
typedef int (*MqttNetDisconnectCb)(void *context);

/* Structure for Network Security */
#ifdef ENABLE_MQTT_TLS
typedef struct _MqttTls {
    WOLFSSL_CTX         *ctx;
    WOLFSSL             *ssl;
    int                 sockRc;
    int                 timeout_ms;
} MqttTls;
#endif

/* Structure for Network callbacks */
typedef struct _MqttNet {
    void                *context;
    MqttNetConnectCb    connect;
    MqttNetReadCb       read;
    MqttNetWriteCb      write;
    MqttNetDisconnectCb disconnect;
#ifdef WOLFMQTT_SN
    MqttNetPeekCb       peek;
    void                *multi_ctx;
#endif
} MqttNet;


/* MQTT SOCKET APPLICATION INTERFACE */
WOLFMQTT_LOCAL int MqttSocket_Init(struct _MqttClient *client, MqttNet* net);
WOLFMQTT_LOCAL int MqttSocket_Write(struct _MqttClient *client, const byte* buf,
        int buf_len, int timeout_ms);
WOLFMQTT_LOCAL int MqttSocket_Read(struct _MqttClient *client, byte* buf,
        int buf_len, int timeout_ms);
#ifdef WOLFMQTT_SN
WOLFMQTT_LOCAL int MqttSocket_Peek(struct _MqttClient *client, byte* buf,
        int buf_len, int timeout_ms);
#endif
WOLFMQTT_LOCAL int MqttSocket_Connect(struct _MqttClient *client,
        const char* host, word16 port, int timeout_ms, int use_tls,
        MqttTlsCb cb);
WOLFMQTT_LOCAL int MqttSocket_Disconnect(struct _MqttClient *client);


#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* WOLFMQTT_SOCKET_H */
