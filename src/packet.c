#include "../include/packet.h"
// #include <packet.h>


void joycon_packet_mcu_read_ack_encode(uint8_t *buffer, uint8_t timer, uint8_t index)
{
    memset(buffer, 0, 64);
    struct PacketMCUReadComm *pkt = (struct PacketMCUReadComm *)buffer;
    pkt->header.command = MCURead;
    pkt->header.counter = timer;

    pkt->subcommand = 0x03;
    pkt->conf.command.command = 0x00;
    pkt->conf.comm_conf.ack_index = index;
    pkt->crc = mcu_crc8(&pkt->conf, MCU_CONF_LEN);
    pkt->padding = 0xFF;
}

void joycon_packet_mcu_read_req_encode(uint8_t *buffer, uint8_t timer, uint8_t index)
{
    memset(buffer, 0, 64);
    struct PacketMCUReadComm *pkt = (struct PacketMCUReadComm *)buffer;
    pkt->header.command = MCURead;
    pkt->header.counter = timer;

    pkt->subcommand = 0x03;
    pkt->conf.command.command = 0x00;
    pkt->conf.command.subcommand = 0x01;
    pkt->conf.comm_conf.req_index = index;
    pkt->crc = mcu_crc8(&pkt->conf, MCU_CONF_LEN);
    pkt->padding = 0xFF;
}

void joycon_packet_mcu_conf_mode(uint8_t *buffer, uint8_t timer, uint8_t mode)
{
    struct PacketMCUConf *pkt = (struct PacketMCUConf *)buffer;
    pkt->header.command = Subcommand;
    pkt->header.counter = timer;
    pkt->subcommand = SetMCUConf;
    pkt->conf.command.command = 0x21;
    pkt->conf.command.subcommand = 0x00;
    pkt->conf.mode_conf.mode = mode;
    pkt->crc = mcu_crc8(&pkt->conf.mode_conf, MCU_CONF_LEN);
}

void joycon_packet_mcu_conf_ir_mode(uint8_t *buffer, uint8_t timer, uint8_t mode, uint8_t number)
{
    struct PacketMCUConf *pkt = (struct PacketMCUConf *)buffer;
    pkt->header.command = Subcommand;
    pkt->header.counter = timer;
    pkt->subcommand = SetMCUConf;
    pkt->conf.command.command = 0x23;
    pkt->conf.command.subcommand = 0x01;
    pkt->conf.ir_conf.ir_mode.mode = mode;
    pkt->conf.ir_conf.ir_mode.number = number;

    // Static version
    pkt->conf.ir_conf.ir_mode.major_version.high = 0x00;
    pkt->conf.ir_conf.ir_mode.major_version.low = 0x05;
    pkt->conf.ir_conf.ir_mode.minor_version.high = 0x00;
    pkt->conf.ir_conf.ir_mode.minor_version.low = 0x18;

    pkt->crc = mcu_crc8(&pkt->conf.ir_conf, MCU_CONF_LEN);
}
