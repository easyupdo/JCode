def ws_accept_key(ws_key):
    """calc the Sec-WebSocket-Accept key by Sec-WebSocket-key
    come from client, the return value used for handshake
 
    :ws_key: Sec-WebSocket-Key come from client
    :returns: Sec-WebSocket-Accept
 
    """
    import hashlib
    import base64
    try:
        magic = '258EAFA5-E914-47DA-95CA-C5AB0DC85B11'
        sha1 = hashlib.sha1()
        sha1.update(ws_key + magic)
        print sha1.digest()
        return base64.b64encode(sha1.digest())
    except Exception as e:
        return None
print ws_accept_key('sN9cRrP/n9NdMgdcy2VJFQ==')