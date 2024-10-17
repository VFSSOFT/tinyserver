
#ifndef TINYSERVER_TEST_LIST_H
#define TINYSERVER_TEST_LIST_H


#include "tinyunit.h"


TEST_DECLARE(invalid_local_host)
TEST_DECLARE(invalid_local_host_2)
TEST_DECLARE(invalid_ssl_cert)

TEST_DECLARE(tcp_connect)
TEST_DECLARE(tls_connect)
TEST_DECLARE(ws_connect)
TEST_DECLARE(wss_connect)
TEST_DECLARE(tcp_server_disconnect)
TEST_DECLARE(tls_server_disconnect)
TEST_DECLARE(ws_server_disconnect)
TEST_DECLARE(wss_server_disconnect)

TEST_DECLARE(tcp_connect_disconnect_quick)
TEST_DECLARE(tls_connect_disconnect_quick)
TEST_DECLARE(ws_connect_disconnect_quick)
TEST_DECLARE(wss_connect_disconnect_quick)
TEST_DECLARE(tcp_connect_disconnect_1s)
TEST_DECLARE(tls_connect_disconnect_1s)
TEST_DECLARE(ws_connect_disconnect_1s)
TEST_DECLARE(wss_connect_disconnect_1s)

TEST_DECLARE(tcp_10clients_connect)
TEST_DECLARE(tls_10clients_connect)
TEST_DECLARE(ws_10clients_connect)
TEST_DECLARE(wss_10clients_connect)
TEST_DECLARE(tcp_100clients_connect)
TEST_DECLARE(tls_100clients_connect)
TEST_DECLARE(ws_100clients_connect)
TEST_DECLARE(wss_100clients_connect)

TEST_DECLARE(tcp_echo)
TEST_DECLARE(tls_echo)
TEST_DECLARE(ws_echo)
TEST_DECLARE(wss_echo)
TEST_DECLARE(tcp_echo_1k)
TEST_DECLARE(tls_echo_1k)
TEST_DECLARE(ws_echo_1k)
TEST_DECLARE(wss_echo_1k)
TEST_DECLARE(tcp_echo2)
TEST_DECLARE(tls_echo2)
TEST_DECLARE(ws_echo2)
TEST_DECLARE(wss_echo2)
TEST_DECLARE(tcp_echo_1k_data)
TEST_DECLARE(tls_echo_1k_data)
TEST_DECLARE(ws_echo_1k_data)
TEST_DECLARE(wss_echo_1k_data)
TEST_DECLARE(tcp_echo_10m_data)
TEST_DECLARE(tls_echo_10m_data)
TEST_DECLARE(ws_echo_10m_data)
TEST_DECLARE(wss_echo_10m_data)

TEST_DECLARE(write_event_tcp_1b)
TEST_DECLARE(write_event_tls_1b)
TEST_DECLARE(write_event_ws_1b)
TEST_DECLARE(write_event_wss_1b)
TEST_DECLARE(write_event_tcp_1b_10)
TEST_DECLARE(write_event_tls_1b_10)
TEST_DECLARE(write_event_ws_1b_10)
TEST_DECLARE(write_event_wss_1b_10)

TEST_DECLARE(tls_invalid_handshake_record_test)
TEST_DECLARE(tls_invalid_handshake_record_1kzero_test)

TEST_DECLARE(mqtt_connect_tcp)
TEST_DECLARE(mqtt_connect_tls)
TEST_DECLARE(mqtt_connect_ws)
TEST_DECLARE(mqtt_connect_wss)

TEST_DECLARE(mqtt_auth_user)
TEST_DECLARE(mqtt_auth_user_fail)
TEST_DECLARE(mqtt_two_clients_with_same_clientid_tcp)
TEST_DECLARE(mqtt_two_clients_with_same_clientid_tls)
TEST_DECLARE(mqtt_two_clients_with_same_clientid_ws)
TEST_DECLARE(mqtt_two_clients_with_same_clientid_wss)

TEST_DECLARE(mqtt_invalid_protocol_tcp_tls_test)
TEST_DECLARE(mqtt_invalid_protocol_tcp_ws_test)
TEST_DECLARE(mqtt_invalid_protocol_tcp_wss_test)
TEST_DECLARE(mqtt_invalid_protocol_tls_tcp_test)
TEST_DECLARE(mqtt_invalid_protocol_tls_ws_test)
TEST_DECLARE(mqtt_invalid_protocol_tls_wss_test)
TEST_DECLARE(mqtt_invalid_protocol_ws_tcp_test)
TEST_DECLARE(mqtt_invalid_protocol_ws_tls_test)
TEST_DECLARE(mqtt_invalid_protocol_ws_wss_test)
TEST_DECLARE(mqtt_invalid_protocol_wss_tcp_test)
TEST_DECLARE(mqtt_invalid_protocol_wss_tls_test)
TEST_DECLARE(mqtt_invalid_protocol_wss_ws_test)

TEST_DECLARE(mqtt_connect_invalid_reserved_flag_test)
TEST_DECLARE(mqtt_invalid_first_pkt_test)
TEST_DECLARE(mqtt_two_connect_pkts)
TEST_DECLARE(mqtt_invalid_protocol_name_test)
TEST_DECLARE(mqtt_valid_protocol_level_test)
TEST_DECLARE(mqtt_zero_clientid_but_not_clean_session_test)
TEST_DECLARE(mqtt_invalid_will_flag_test)
TEST_DECLARE(mqtt_invalid_will_qos_test)
TEST_DECLARE(mqtt_invalid_user_name_flag_test)
TEST_DECLARE(mqtt_invalid_user_password_flag_test)
TEST_DECLARE(mqtt_empty_subscribe)
TEST_DECLARE(mqtt_subscribe_invalid_reserved)
TEST_DECLARE(mqtt_subscribe_invalid_qos)
TEST_DECLARE(mqtt_subscribe_invalid_topic)
TEST_DECLARE(mqtt_empty_unsubscribe)
TEST_DECLARE(mqtt_unsubscribe_invalid_reserved)
TEST_DECLARE(mqtt_unsubscribe_invalid_topic)
TEST_DECLARE(mqtt_unsubscribe_zero_pkt_id)
TEST_DECLARE(mqtt_publish_qos3)
TEST_DECLARE(mqtt_publish_qos0_with_dup)

TEST_DECLARE(mqtt_conn_ack_sp_false_test)
TEST_DECLARE(mqtt_conn_ack_sp_true_test)
TEST_DECLARE(mqtt_zero_length_client_id_test)
TEST_DECLARE(mqtt_normal_client_id_test)
TEST_DECLARE(mqtt_512_length_client_id_test)
TEST_DECLARE(mqtt_too_long_client_id_test)

TEST_DECLARE(mqtt_keep_alive_test)
TEST_DECLARE(mqtt_keep_alive_zero_test)
TEST_DECLARE(mqtt_keep_alive_timed_out_test)
TEST_DECLARE(mqtt_no_pkt_after_connected_test)

TEST_DECLARE(mqtt_valid_topic_name_test)
TEST_DECLARE(mqtt_valid_topic_filter_test)
TEST_DECLARE(mqtt_invalid_topic_name_test)
TEST_DECLARE(mqtt_invalid_topic_filter_test)
TEST_DECLARE(mqtt_invalid_topic_name_null_test)
TEST_DECLARE(mqtt_invalid_topic_filter_null_test)
TEST_DECLARE(mqtt_sub_matched_test)
TEST_DECLARE(mqtt_sub_unmatched_test)
TEST_DECLARE(mqtt_sub_matched_multiple_test)
TEST_DECLARE(mqtt_sub_matched_multiple_test2)
TEST_DECLARE(mqtt_sub_unsub_test)
TEST_DECLARE(mqtt_sub_unsub_unmatched_test)
TEST_DECLARE(mqtt_retain_msg_test)
TEST_DECLARE(mqtt_retain_msg_update_test)
TEST_DECLARE(mqtt_retain_msg_delete_test)
TEST_DECLARE(mqtt_get_retain_msg_not_found_test)

TEST_DECLARE(mqtt_sub_unsub_qos_0_test)
TEST_DECLARE(mqtt_sub_unsub_qos_1_test)
TEST_DECLARE(mqtt_sub_unsub_qos_2_test)
TEST_DECLARE(mqtt_unsub_non_exist_qos_0_test)
TEST_DECLARE(mqtt_unsub_non_exist_qos_1_test)
TEST_DECLARE(mqtt_unsub_non_exist_qos_2_test)
TEST_DECLARE(mqtt_unsub_non_exist_test_2)
TEST_DECLARE(mqtt_unsub_non_exist_test_3)
TEST_DECLARE(mqtt_sub_unsub_many_test1)
TEST_DECLARE(mqtt_sub_unsub_many_test2)
TEST_DECLARE(mqtt_sub_unsub_many_test3)
TEST_DECLARE(mqtt_max_qos_of_all_subscriptions)
TEST_DECLARE(mqtt_update_subscribe_qos)
TEST_DECLARE(mqtt_update_subscribe_qos_resent_retain_msg)
TEST_DECLARE(mqtt_grant_low_qos_value)

TEST_DECLARE(mqtt_basic_pub_qos0_test)
TEST_DECLARE(mqtt_basic_pub_qos1_test)
TEST_DECLARE(mqtt_basic_pub_qos2_test)

TEST_DECLARE(mqtt_basic_pub_recv_qos0_tcp)
TEST_DECLARE(mqtt_basic_pub_recv_qos1_tcp)
TEST_DECLARE(mqtt_basic_pub_recv_qos2_tcp)
TEST_DECLARE(mqtt_pub_qos_0_sub_qos_1_tcp)
TEST_DECLARE(mqtt_pub_qos_0_sub_qos_2_tcp)
TEST_DECLARE(mqtt_pub_qos_1_sub_qos_0_tcp)
TEST_DECLARE(mqtt_pub_qos_1_sub_qos_2_tcp)
TEST_DECLARE(mqtt_pub_qos_2_sub_qos_0_tcp)
TEST_DECLARE(mqtt_pub_qos_2_sub_qos_1_tcp)

TEST_DECLARE(mqtt_recv_offline_msgs_after_reconnect)
TEST_DECLARE(mqtt_no_offline_msgs_after_reconnect_with_clean_session)

TEST_DECLARE(mqtt_not_pub_will_if_client_disconnect_normally)
TEST_DECLARE(mqtt_pub_will_if_client_disconnect_abnormally)
TEST_DECLARE(mqtt_pub_will_if_client_disconnect_abnormally_retain)

TEST_DECLARE(mqtt_retain_msg_current_subscription)
TEST_DECLARE(mqtt_retain_msg_new_subscription)
TEST_DECLARE(mqtt_retain_msg_zero_byte)
TEST_DECLARE(mqtt_retain_msg_zero_byte_1)
TEST_DECLARE(mqtt_retain_msg_zero_byte_2)
TEST_DECLARE(mqtt_retain_msg_zero_byte_3)
TEST_DECLARE(mqtt_retain_msg_update_exist)
TEST_DECLARE(mqtt_retain_msg_kept_after_publisher_session_ends)

TEST_DECLARE(mqtt_msg_delivery_resend_puback)
TEST_DECLARE(mqtt_msg_delivery__server_resend_publish_qos2)
TEST_DECLARE(mqtt_msg_delivery__server_resend_pubrel)

TEST_LIST_START
        TEST_ENTRY(invalid_local_host, "Error")
        TEST_ENTRY(invalid_local_host_2, "Error")
        TEST_ENTRY(invalid_ssl_cert, "Error")
        
        TEST_ENTRY(tcp_connect, "TCP")
        TEST_ENTRY(tls_connect, "TLS")
        TEST_ENTRY(ws_connect, "Websocket")
        TEST_ENTRY(wss_connect, "Websocket,TLS")
        TEST_ENTRY(tcp_server_disconnect, "TCP")
        TEST_ENTRY(tls_server_disconnect, "TLS")
        TEST_ENTRY(ws_server_disconnect, "Websocket")
        TEST_ENTRY(wss_server_disconnect, "Websocket,TLS")
        TEST_ENTRY(tcp_connect_disconnect_quick, "TCP")
        TEST_ENTRY(tls_connect_disconnect_quick, "TLS")
        TEST_ENTRY(ws_connect_disconnect_quick, "Websocket")
        TEST_ENTRY(wss_connect_disconnect_quick, "Websocket,TLS")
        
        TEST_ENTRY(tcp_connect_disconnect_1s, "TCP")
        TEST_ENTRY(tls_connect_disconnect_1s, "TLS")
        TEST_ENTRY(ws_connect_disconnect_1s, "Websocket")
        TEST_ENTRY(wss_connect_disconnect_1s, "Websocket,TLS")
        
        TEST_ENTRY(tcp_10clients_connect, "TCP")
        TEST_ENTRY(tls_10clients_connect, "TLS")
        TEST_ENTRY(ws_10clients_connect, "Websocket")
        TEST_ENTRY(wss_10clients_connect, "TLS,Websocket")
        TEST_ENTRY(tcp_100clients_connect, "TCP")
        TEST_ENTRY(tls_100clients_connect, "TLS")
        TEST_ENTRY(ws_100clients_connect, "Websocket")
        TEST_ENTRY(wss_100clients_connect, "TLS,Websocket")
        

        TEST_ENTRY(tcp_echo, "TCP")
        TEST_ENTRY(tls_echo, "TLS")
        TEST_ENTRY(ws_echo, "Websocket")
        TEST_ENTRY(wss_echo, "TLS,Websocket")
        TEST_ENTRY(tcp_echo_1k, "TCP")
        TEST_ENTRY(tls_echo_1k, "TLS")
        TEST_ENTRY(ws_echo_1k, "Websocket")
        TEST_ENTRY(wss_echo_1k, "TLS,Websocket")
        TEST_ENTRY(tcp_echo2, "TCP")
        TEST_ENTRY(tls_echo2, "TLS")
        TEST_ENTRY(ws_echo2, "Websocket")
        TEST_ENTRY(tls_echo2, "TLS,Websocket")
        TEST_ENTRY(tcp_echo_1k_data, "TCP")
        TEST_ENTRY(tls_echo_1k_data, "TLS")
        TEST_ENTRY(ws_echo_1k_data, "Websocket")
        TEST_ENTRY(wss_echo_1k_data, "TLS,Websocket")
        TEST_ENTRY(tcp_echo_10m_data, "TCP")
        TEST_ENTRY(tls_echo_10m_data, "TLS")
        TEST_ENTRY(ws_echo_10m_data, "Websocket")
        TEST_ENTRY(wss_echo_10m_data, "TLS,Websocket")
        TEST_ENTRY(write_event_tcp_1b, "TCP")
        TEST_ENTRY(write_event_tls_1b, "TLS")
        TEST_ENTRY(write_event_ws_1b, "Websocket")
        TEST_ENTRY(write_event_wss_1b, "TLS,Websocket")
        TEST_ENTRY(write_event_tcp_1b_10, "TCP")
        TEST_ENTRY(write_event_tls_1b_10, "TLS")
        TEST_ENTRY(write_event_ws_1b_10, "Websocket")
        TEST_ENTRY(write_event_wss_1b_10, "TLS,Websocket")

        TEST_ENTRY(tls_invalid_handshake_record_test, "TLS")
        TEST_ENTRY(tls_invalid_handshake_record_1kzero_test, "TLS")

        TEST_ENTRY(mqtt_connect_tcp, "TCP,MQTT")
        TEST_ENTRY(mqtt_connect_tls, "TLS,MQTT")
        TEST_ENTRY(mqtt_connect_ws, "Websocket,MQTT")
        TEST_ENTRY(mqtt_connect_wss, "Websocket,TLS,MQTT")
        
        TEST_ENTRY(mqtt_auth_user, "MQTT")
        TEST_ENTRY(mqtt_auth_user_fail, "MQTT")
        TEST_ENTRY(mqtt_two_clients_with_same_clientid_tcp, "TCP,MQTT")
        TEST_ENTRY(mqtt_two_clients_with_same_clientid_tls, "TLS,MQTT")
        TEST_ENTRY(mqtt_two_clients_with_same_clientid_ws, "Websocket,MQTT")
        TEST_ENTRY(mqtt_two_clients_with_same_clientid_wss, "Websocket,TLS,MQTT")

        TEST_ENTRY(mqtt_invalid_protocol_tcp_tls_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_tcp_ws_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_tcp_wss_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_tls_tcp_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_tls_ws_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_tls_wss_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_ws_tcp_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_ws_tls_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_ws_wss_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_wss_tcp_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_wss_tls_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_wss_ws_test, "MQTT")

        TEST_ENTRY(mqtt_connect_invalid_reserved_flag_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_first_pkt_test, "MQTT")
        TEST_ENTRY(mqtt_two_connect_pkts, "MQTT")
        TEST_ENTRY(mqtt_invalid_protocol_name_test, "MQTT")
        TEST_ENTRY(mqtt_valid_protocol_level_test, "MQTT")
        TEST_ENTRY(mqtt_zero_clientid_but_not_clean_session_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_will_flag_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_will_qos_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_user_name_flag_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_user_password_flag_test, "MQTT")
        TEST_ENTRY(mqtt_empty_subscribe, "MQTT")
        TEST_ENTRY(mqtt_subscribe_invalid_reserved, "MQTT")
        TEST_ENTRY(mqtt_subscribe_invalid_qos, "MQTT")
        TEST_ENTRY(mqtt_subscribe_invalid_topic, "MQTT")
        TEST_ENTRY(mqtt_empty_unsubscribe, "MQTT")
        TEST_ENTRY(mqtt_unsubscribe_invalid_reserved, "MQTT")
        TEST_ENTRY(mqtt_unsubscribe_invalid_topic, "MQTT")
        TEST_ENTRY(mqtt_unsubscribe_zero_pkt_id, "MQTT")
        TEST_ENTRY(mqtt_publish_qos3, "MQTT")
        TEST_ENTRY(mqtt_publish_qos0_with_dup, "MQTT")
        
        TEST_ENTRY(mqtt_conn_ack_sp_false_test, "MQTT")
        TEST_ENTRY(mqtt_conn_ack_sp_true_test, "MQTT")
        TEST_ENTRY(mqtt_zero_length_client_id_test, "MQTT")
        TEST_ENTRY(mqtt_normal_client_id_test, "MQTT")
        TEST_ENTRY(mqtt_512_length_client_id_test, "MQTT")
        TEST_ENTRY(mqtt_too_long_client_id_test, "MQTT")

        TEST_ENTRY(mqtt_keep_alive_test, "MQTT")
        TEST_ENTRY(mqtt_keep_alive_zero_test, "MQTT")
        TEST_ENTRY(mqtt_keep_alive_timed_out_test, "MQTT")
        TEST_ENTRY(mqtt_no_pkt_after_connected_test, "MQTT")

        TEST_ENTRY(mqtt_valid_topic_name_test, "MQTT")
        TEST_ENTRY(mqtt_valid_topic_filter_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_topic_name_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_topic_filter_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_topic_name_null_test, "MQTT")
        TEST_ENTRY(mqtt_invalid_topic_filter_null_test, "MQTT")
        TEST_ENTRY(mqtt_sub_matched_test, "MQTT")
        TEST_ENTRY(mqtt_sub_unmatched_test, "MQTT")
        TEST_ENTRY(mqtt_sub_matched_multiple_test, "MQTT")
        TEST_ENTRY(mqtt_sub_matched_multiple_test2, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_test, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_unmatched_test, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_test, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_update_test, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_delete_test, "MQTT")
        TEST_ENTRY(mqtt_get_retain_msg_not_found_test, "MQTT")

        TEST_ENTRY(mqtt_sub_unsub_qos_0_test, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_qos_1_test, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_qos_2_test, "MQTT")
        TEST_ENTRY(mqtt_unsub_non_exist_qos_0_test, "MQTT")
        TEST_ENTRY(mqtt_unsub_non_exist_qos_1_test, "MQTT")
        TEST_ENTRY(mqtt_unsub_non_exist_qos_2_test, "MQTT")
        TEST_ENTRY(mqtt_unsub_non_exist_test_2, "MQTT")
        TEST_ENTRY(mqtt_unsub_non_exist_test_3, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_many_test1, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_many_test2, "MQTT")
        TEST_ENTRY(mqtt_sub_unsub_many_test3, "MQTT")
        TEST_ENTRY(mqtt_max_qos_of_all_subscriptions, "MQTT")
        TEST_ENTRY(mqtt_update_subscribe_qos, "MQTT")
        TEST_ENTRY(mqtt_update_subscribe_qos_resent_retain_msg, "MQTT")
        TEST_ENTRY(mqtt_grant_low_qos_value, "MQTT")

        TEST_ENTRY(mqtt_basic_pub_qos0_test, "MQTT")
        TEST_ENTRY(mqtt_basic_pub_qos1_test, "MQTT")
        TEST_ENTRY(mqtt_basic_pub_qos2_test, "MQTT")
        TEST_ENTRY(mqtt_basic_pub_recv_qos0_tcp, "MQTT")
        TEST_ENTRY(mqtt_basic_pub_recv_qos1_tcp, "MQTT")
        TEST_ENTRY(mqtt_basic_pub_recv_qos2_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_0_sub_qos_1_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_0_sub_qos_2_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_1_sub_qos_0_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_1_sub_qos_2_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_2_sub_qos_0_tcp, "MQTT")
        TEST_ENTRY(mqtt_pub_qos_2_sub_qos_1_tcp, "MQTT")

        TEST_ENTRY(mqtt_recv_offline_msgs_after_reconnect, "MQTT")
        TEST_ENTRY(mqtt_no_offline_msgs_after_reconnect_with_clean_session, "MQTT")

        TEST_ENTRY(mqtt_not_pub_will_if_client_disconnect_normally, "MQTT")
        TEST_ENTRY(mqtt_pub_will_if_client_disconnect_abnormally, "MQTT")
        TEST_ENTRY(mqtt_pub_will_if_client_disconnect_abnormally_retain, "MQTT")

        TEST_ENTRY(mqtt_retain_msg_current_subscription, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_new_subscription, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_zero_byte, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_zero_byte_1, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_zero_byte_2, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_zero_byte_3, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_update_exist, "MQTT")
        TEST_ENTRY(mqtt_retain_msg_kept_after_publisher_session_ends, "MQTT")


        TEST_ENTRY(mqtt_msg_delivery_resend_puback, "MQTT")
        TEST_ENTRY(mqtt_msg_delivery__server_resend_publish_qos2, "MQTT")
        TEST_ENTRY(mqtt_msg_delivery__server_resend_pubrel, "MQTT")
TEST_LIST_END

#endif //TINYSERVER_TEST_LIST_H
