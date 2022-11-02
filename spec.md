## Gateway Structures

### PACKET
| Field | Type    | Description    |
|-------|---------|----------------|
| op    | integer | Packet opcode  |
| d     | mixed   | Packet payload |

### MESSAGE
| Field     | Type    | Description                 |
|-----------|---------|-----------------------------|
| sender    | string  | Sender nickname             |
| timestamp | integer | Message sent epoch seconds  |
| body      | string  | Message body (100 char max) |

## Gateway Methods

### WELCOME

**Origin**: Server

**opcode**: ``0x01``

### JOIN

**Origin**: Client

**opcode**: ``0x02``

| Field | Type   | Description                 |
|-------|--------|-----------------------------|
| nick  | string | The requested user nickname |

### ONBOARD

**Origin**: Server

**opcode**: ``0x03``

| Field | Type                     | Description                      |
|-------|--------------------------|----------------------------------|
| resp  | int                      | Response code to CONNECT attempt |
| msgs  | array\<MESSAGE\> or null | Existing chatroom messages       |

##### Response codes

| Code | Meaning                |
|------|------------------------|
| 0    | Successfully connected |
| -1   | Chatroom full          |
| -2   | Username unavailable   |

### SEND_MSG

**Origin**: Client

**opcode**: ``0x04``

| Field | Type    | Description |
|-------|---------|-------------|
| msg   | MESSAGE | New message |

### SEND_MSG_ACK

**Origin**: Server

**opcode**: ``0x05``

| Field     | Type    | Description          |
|-----------|---------|----------------------|
| timestamp | integer | Timestamp of message |

### NEW_MSGS

**Origin**: Server

**opcode**: ``0x06``

| Field | Type                     | Description           |
|-------|--------------------------|-----------------------|
| msgs  | array\<MESSAGE\> or null | New chatroom messages |