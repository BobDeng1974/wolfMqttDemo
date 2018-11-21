
#ifndef WOLFMQTT_NET_H
#define WOLFMQTT_NET_H

#ifdef __cplusplus
    extern "C" {
#endif


/* Default MQTT host broker to use, when none is specified in the examples */
#define DEFAULT_MQTT_HOST       "iot.eclipse.org" /* broker.hivemq.com */

/* Functions used to handle the MqttNet structure creation / destruction */
int MqttClientNet_Init(MqttNet* net);
int MqttClientNet_DeInit(MqttNet* net);
#ifdef WOLFMQTT_SN
int SN_ClientNet_Init(MqttNet* net);
#endif

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* WOLFMQTT_NET_H */
