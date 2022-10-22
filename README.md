# simple-chatroom

## A basic CLI chatroom written in C++

## Features

1. Users can join a chatroom from a CLI

2. The server is multi-threaded

3. Messages are consistent, and cached through restarts

4. Upon joining, users will select a nickname and can view the cached messages

## Gateway Structures

### PACKET
| Field | Type    | Description    |
|-------|---------|----------------|
| op    | integer | Packet opcode  |
| d     | mixed   | Packet payload |

## Gateway Packets

### CONNECT

**Origin**: Client

**opcode**: ``0x01``

| Field | Type   | Description                 |
|-------|--------|-----------------------------|
| nick  | string | The requested user nickname |

### WELCOME

**Origin**: Server

**opcode**: ``0x02``

| Field | Type | Description                                          |
|-------|------|------------------------------------------------------|
| resp  | int  | Response code to CONNECT attempt |
| 

##### Response codes

| Code | Meaning                |
|------|------------------------|
| 0    | Successfully connected |
| -1   | Chatroom full          |
| -2   | Username unavailable   |