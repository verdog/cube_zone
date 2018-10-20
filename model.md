1. Connection
    1. Client sends "Hi, I'm here, send messages to this port" message to server
    2. Server recieves "Hi, I'm here" message. Creates server-side cube.
    3. Server sends message back: "You've been accepted."

2. Gameplay
    1. Asks server for info.
    2. Server responds, updates the client's ttl.

3. Disconnect
    1. Client sends "Goodbye"
    2. Server recieves and deletes object.